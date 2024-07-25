using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Text;
using Google.Protobuf;
using FakeData.Analysis;

namespace Test_NaiveParsing
{
    public class Program
    {
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

            Dictionary<string, int> res = new Dictionary<string, int>();

            foreach (string filePath in filePaths)
            {
                Console.WriteLine($"Processing {filePath}...");
                ApplyAggregation(res, filePath);
            }
            foreach (var ipair in res)
            {
                Console.WriteLine("{0}:{1}", ipair.Key, ipair.Value);
            }
        }

        private static void ApplyAggregation(Dictionary<string, int> res, string filePath)
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
                AggDistribution_Boxes(res, data);
            }
        }

        private static void AggDistribution_Boxes(Dictionary<string, int> res, FakeAnaData data)
        {
            int binCost = 0;

            if (!res.Keys.Contains("nevents"))
                res["nevents"] = 0;
            if (!res.Keys.Contains("nboxes"))
                res["nboxes"] = 0;

            res["nevents"] += data.History.Count();
            foreach (var history_i in data.History)
            {
                res["nboxes"] += history_i.Boxes.Count();
                foreach (var box_j in history_i.Boxes)
                {
                    binCost = (int)(box_j.Cost > 0 ? Math.Floor(10*Math.Log10(box_j.Cost)) : -99);
                    var strBinCost = Convert.ToString(binCost);
                    if (!res.Keys.Contains(strBinCost))
                        res[strBinCost] = 0;
                    res[strBinCost] += box_j.Count;
                }
            }
        }
    }
}

