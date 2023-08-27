import subprocess
import matplotlib.pyplot as plt
import numpy as np
import re
import statistics
from tabulate import tabulate

def compile_and_run(buffer_size, num_runs=10):
    command = ["gcc", "-o", "read", "read.c"]
    if buffer_size > 0:
        command.append("-DBUFFER_SIZE={}".format(buffer_size))
    subprocess.run(command)

    command = ["time", "./read", f"{buffer_size}"]
    p = subprocess.run(command, capture_output=True, text=True)
    clock_times = []
    user_times = []
    sys_times = []
    for i in range(num_runs):
        for line in p.stderr.splitlines():
            clock_time, user_time, sys_time = re.findall(r'(\d+\.\d+)', line)
            clock_times.append(float(clock_time))
            user_times.append(float(user_time))
            sys_times.append(float(sys_time))
    
    command = ["rm", "read"]
    subprocess.run(command)

    return statistics.median(clock_times), statistics.median(user_times), statistics.median(sys_times)


if __name__ == "__main__":
    buffer_sizes = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]
    headers = ["Buffer Size", "Clock Time", "User Time", "System Time"]
    table_data = []
    clock_times = []
    user_times = []
    sys_times = []
    for buffer_size in buffer_sizes:
        clock_time, user_time, sys_time = compile_and_run(buffer_size)
        clock_times.append(clock_time)
        user_times.append(user_time)
        sys_times.append(sys_time)
        table_data.append([buffer_size, clock_time, user_time, sys_time])

    table_output = tabulate(table_data, headers=headers, tablefmt="grid")
    print(table_output)

    with open("./tables/buffer_size measurement.txt", "w") as file:
        file.write(table_output)

    plt.figure(figsize=(10, 6))
    plt.plot(buffer_sizes, clock_times, label='Clock Time')
    plt.plot(buffer_sizes, user_times, label='User Time')
    plt.plot(buffer_sizes, sys_times, label='System Time')

    plt.xlabel('Buffer Size')
    plt.ylabel('Time')
    plt.title('Time Measurements of read Operation')
    plt.legend()
    plt.grid(True)
    plt.xscale('log')
    plt.xticks(buffer_sizes, buffer_sizes)
    plt.savefig('./figures/buffer_size measurement.png')