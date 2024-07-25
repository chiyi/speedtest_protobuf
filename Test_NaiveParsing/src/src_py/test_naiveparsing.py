import sys
import glob
import gzip
import math
import base64
from collections import defaultdict
from fake_anadata_pb2 import FakeAnaData


def get_files(format="/data/"):
    return glob.glob(format) 

def aggregate_boxes(out, data):
    history = data.history
    nevts = len(history)
    out['nevents'] += nevts
    for history_i in history:
        nboxes = len(history_i.boxes)
        out['nboxes'] += nboxes
        for box_j in history_i.boxes:
            bin_cost = math.floor(10 * math.log10(box_j.cost)) if box_j.cost > 0 else -99
            out[bin_cost] += box_j.count
    return out

def process_file(out, inpfile):
    delim = b'\001\002\003\004\005\006\007\010\n'
    with gzip.open(inpfile, 'rb') as fr:
        lines = fr.readlines()
    for line in lines:
        if not line.endswith(delim):
            print("WARN: Unexpected Newline detected !!!\n")
            continue
        line = line[: len(line) - 9]
        data = FakeAnaData.FromString(base64.b64decode(line))
        out = aggregate_boxes(out, data)
    return out

def process_file_light(out, inpfile):  # if OOM
    delim = b'\001\002\003\004\005\006\007\010\n'
    with gzip.open(inpfile, 'rb') as fr:
        for line in fr:
            if not line.endswith(delim):
                print("WARN: Unexpected Newline detected !!!\n")
                continue
            line = line[: len(line) - 9]
            data = FakeAnaData.FromString(base64.b64decode(line))
            out = aggregate_boxes(out, data)
    return out




def test_naiveparsing(argv):
    res = defaultdict(int)
    filenames = get_files(argv[1])
    for ifile in filenames:
        print("processing {}...".format(ifile))
        res = process_file(res, ifile)
    print(res)

if __name__ == '__main__':
    print('sys.argv=', sys.argv)
    if 'test_naiveparsing.py' in sys.argv[0]:
        test_naiveparsing(sys.argv)

