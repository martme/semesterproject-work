import subprocess


def main():
    values = []
    for i in range(100):
        c_A = count_misses_in_A();
        c_B = count_misses_in_B();
        values.append(c_A - c_B)
    print sum(values) / len(values)


def count_misses_in_A():
    cmd = 'perf stat -e cache-misses:u bin/1k_cache_miss'.split()
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    err, out = p.communicate()

    line = out.split("\n")[3].strip()
    return int(line[:line.index(' ')].replace("\xc2\xa0", ""))

def count_misses_in_B():
    cmd = 'perf stat -e cache-misses:u bin/1k_cache_hit'.split()
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    err, out = p.communicate()

    line = out.split("\n")[3].strip()
    return int(line[:line.index(' ')].replace("\xc2\xa0", ""))

main()
