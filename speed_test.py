import matplotlib.pyplot as plt
import subprocess

bash_cmd = "qemu-riscv64-static speed_test"

# We're going to run the subprocess multiple times with varying buffer sizes
powers_of_two = [2**(i * 2) for i in range(1, 16)]
outputs = []
for power in powers_of_two:
    process = subprocess.run(bash_cmd.split() + [str(power)], 
                             stdout=subprocess.PIPE, 
                             stderr=subprocess.PIPE, 
                             check=True, 
                             text=True)
    outputs.append(process.stdout.split(","))


# We expect the data to be in 
for result in outputs:
    print(result)

# Now we can plot the data
plt.plot(powers_of_two, [float(result[0]) for result in outputs], 'r', label='glibc memset')
plt.plot(powers_of_two, [float(result[1]) for result in outputs], 'b', label='example memset')
plt.plot(powers_of_two, [float(result[2]) for result in outputs], 'g', label='custom memset')
plt.xscale('log', base=2)
plt.xticks(powers_of_two)
plt.xlabel('Buffer Size (Bytes)')
plt.ylabel('Time (s)')
plt.title("Speed comparison of glibc memset, the example memset, and my custom memset")
plt.legend()
plt.savefig("speed_comparison.png")






