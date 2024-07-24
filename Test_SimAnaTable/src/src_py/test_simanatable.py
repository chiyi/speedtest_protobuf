import sys
import glob
import gzip
import numpy
import math
import base64
from fake_anadata_pb2 import FakeAnaData


def get_files(format="/data/"):
    return glob.glob(format)

def cal_log10(x):
    return math.log10(x) if x > 0 else -9.9

def filter_1_activated(history_i, selblock):
    blocks = {'x': 'blockx', 'y': 'blocky', 'z': 'blockz'}
    if selblock not in blocks:
        return False
    return history_i.HasField(blocks[selblock]) and len(getattr(history_i, blocks[selblock]).id_z) > 0

def get_log10median(data, selblock):
    filtered_blocks = (history_i for history_i in data.history if filter_1_activated(history_i, selblock))
    list_scores = [cal_log10(history_i.score) for history_i in filtered_blocks]
    return numpy.median(list_scores) if list_scores else 0

def cal_rival(out, hashed_name, data):
    data_key = hashed_name
    out[data_key] = out.get(data_key, {'hashed_name': '', 'ts_max': 0, 'val_sim': 0.})
    ts_max = out[data_key]['ts_max']
    val_sim = out[data_key]['val_sim']
    val_x = get_log10median(data, 'x')
    val_y = get_log10median(data, 'y')
    val_z = get_log10median(data, 'z')
    val_sim += val_x + val_y * 888 + val_z * 88888
    ts_max = max(ts_max, max(history_i.timestamp for history_i in data.history))
    out[data_key]['hashed_name'] = hashed_name
    out[data_key]['ts_max'] = ts_max
    out[data_key]['val_sim'] = val_sim
    return out

def filter_0_activated(data):
    return len(data.hashed_name) < 5 or len(data.hashed_name) >= 40 or len(data.history) == 0

def process_file(out, inpfile):
    delim = b'\001\002\003\004\005\006\007\010\n'
    with gzip.open(inpfile, 'rb') as fr:
        lines = fr.readlines()
    for line in lines:
        if not line.endswith(delim):
            print("WARN: Unexpected Newline detected !!!\n")
            continue
        line = line[:-9]
        data = FakeAnaData.FromString(base64.b64decode(line))

        if filter_0_activated(data):
            continue
        out = cal_rival(out, data.hashed_name, data)
    return out

def process_file_light(out, inpfile):  # if OOM
    delim = b'\001\002\003\004\005\006\007\010\n'
    with gzip.open(inpfile, 'rb') as fr:
        for line in fr:
            if not line.endswith(delim):
                print("WARN: Unexpected Newline detected !!!\n")
                continue
            line = line[:-9]
            data = FakeAnaData.FromString(base64.b64decode(line))

            if filter_0_activated(data):
                continue
            out = cal_rival(out, data.hashed_name, data)
    return out

def write_result(out):
    with open("table/pysim_result.txt", 'w') as fw:
        for idx, ikey in enumerate(sorted(out)):
            val = out[ikey]
            outstr = "%10d-th: %s => (%s, %ld, %10.0f)\n" % (idx, ikey, val['hashed_name'], val['ts_max'], val['val_sim']) 
            fw.write(outstr)




def test_simanatable(argv):
    res = dict()
    filenames = get_files(argv[1])
    for ifile in filenames:
        print("processing {}...".format(ifile))
        res = process_file(res, ifile)
    write_result(res)


if __name__ == '__main__':
    print('sys.argv=', sys.argv)
    if 'test_simanatable.py' in sys.argv[0]:
        test_simanatable(sys.argv)
