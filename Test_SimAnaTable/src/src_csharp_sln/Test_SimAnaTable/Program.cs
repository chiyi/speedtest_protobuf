using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using Google.Protobuf;
using FakeData.Analysis;

namespace Test_SimAnaTable
{
    public class Program
    {
        class SimData_Rival
        {
            public long TsMax=0;
            public double ValSim=0.0;
            public string HashedName=string.Empty;

            public SimData_Rival()
            {
            }

            public SimData_Rival(string HashedName, long TsMax, double ValSim)
            {
                this.HashedName = HashedName;
                this.TsMax = TsMax;
                this.ValSim = ValSim;
            }

            public override string ToString()
            {
                return $"({HashedName}, {TsMax}, {ValSim, 10:F0})";
            }
        }

        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: program.exe <directory> <wildcard>");
                return;
            }

            string directory = args[0];
            string wildcard = args[1];

            if (!Directory.Exists(directory))
            {
                Console.WriteLine($"Directory '{directory}' does not exist.");
                return;
            }

            string[] filePaths = Directory.GetFiles(directory, wildcard);

            var res = new SortedDictionary<string, SimData_Rival>();

            foreach (string filePath in filePaths)
            {
                Console.WriteLine($"Processing {filePath}...");
                SimulateAnalysis(res, filePath);
            }

            WriteResult(res);
        }

        private static void WriteResult(SortedDictionary<string, SimData_Rival> res)
        {
            var selkeys = res.Keys.ToList();
            int idx = 0;
            using (var outputFile = new StreamWriter("table/csharpsim_result.txt"))
            {
                foreach (var ikey in res.Keys)
                {
                    var val = res[ikey];
                    string outstr = $"{idx,10}-th: {ikey} => {val}";
                    outputFile.WriteLine(outstr);
                    idx++;
                }
            }
        }

        private static void SimulateAnalysis(SortedDictionary<string, SimData_Rival> res, string filePath)
        {
            List<string> lines = new List<string>();
            using (var fs = File.OpenRead(filePath))
            using (var gz = new GZipStream(fs, CompressionMode.Decompress))
            using (var sr = new StreamReader(gz, Encoding.UTF8))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                    lines.Add(line);
            }

            byte[] delim = { 1, 2, 3, 4, 5, 6, 7, 8 };
            string delimStr = Encoding.ASCII.GetString(delim);

            foreach (var line in lines)
            {
                if (!line.EndsWith(delimStr))
                {
                    Console.WriteLine("WARN: Unexpected Newline detected !!!");
                    continue;
                }
                byte[] decodedLine = Convert.FromBase64String(line.Substring(0, line.Length - 8));
                FakeAnaData data = FakeAnaData.Parser.ParseFrom(decodedLine);

                if(Filter0_Activated(data))
                    continue;

                CalRival(res, data.HashedName, data);
            }
        }

        private static bool Filter0_Activated(FakeAnaData data)
        {
         return data.HashedName.Length < 5 || data.HashedName.Length >= 40 || data.History.Count <= 0;
        }

        private static void CalRival(SortedDictionary<string, SimData_Rival> res, string hashed_name, FakeAnaData data)
        {
            SimData_Rival val;
            if(!res.TryGetValue(hashed_name, out val))
            {
                val = new SimData_Rival();
            }
            var ValX = GetLog10Median(data, 'x');
            var ValY = GetLog10Median(data, 'y');
            var ValZ = GetLog10Median(data, 'z');

            val.HashedName = hashed_name;
            val.ValSim += ValX + ValY * 888 + ValZ * 88888;
            val.TsMax = Math.Max(val.TsMax, data.History.Select(x => x.Timestamp).Max());
            res[hashed_name] = val;
        }

        private static double GetLog10Median(FakeAnaData data, char selblock)
        {
            double res = 0.0;
            int size = 0;
            List<double> vecScore = new List<double>();
        
            foreach (var history_i in data.History)
                if (Filter1_Activated(history_i, selblock))
                    vecScore.Add(CalLog10(history_i.Score));
        
            size = vecScore.Count;
        
            if (size == 0) return res;
        
            vecScore.Sort();
            res = size % 2 == 0 ? (vecScore[size / 2] + vecScore[size / 2 - 1]) * 0.5 : vecScore[size / 2];
        
            return res;
        }

        private static bool Filter1_Activated(Event history_i, char selblock)
        {
            bool res = false;
            switch (selblock)
            {
                case 'x':
                    res = history_i.Blockx != null && !string.IsNullOrEmpty(history_i.Blockx.IdZ);
                    break;
                case 'y':
                    res = history_i.Blocky != null && !string.IsNullOrEmpty(history_i.Blocky.IdZ);
                    break;
                case 'z':
                    res = history_i.Blockz != null && !string.IsNullOrEmpty(history_i.Blockz.IdZ);
                    break;
            }
            return res;
        }

        private static double CalLog10(double value)
        {
            return value > 0 ? Math.Log10(value) : -9.9;
        }
    }
}
