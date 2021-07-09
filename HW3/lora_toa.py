import math
import matplotlib.pyplot as plt

def main():
    
    # Spread Factor (SF)
    sfs = [7, 8, 9, 10, 11, 12]

    # Payload size (bytes)
    pls = [16, 32, 51]

    # Bandwidth
    bw = 125_000

    labels = []
    
    for pl in pls:

        t_on_airs = []

        for sf in sfs:

            n_preample = 8
            n_payload = 8 + max(math.ceil((8 * pl - 4 * sf + 28 + 16) / (4 * (sf - 2))) * (1 + 4), 0)
            t_on_air = ((n_payload + (n_preample + 4.25)) * ((2 ** sf) / bw)) * 1000

            t_on_airs.append(t_on_air)

        l, = plt.plot(sfs, t_on_airs, label=f'{pl} bytes')
        labels.append(l)

    plt.legend(handles=labels)
    plt.xlabel('Spread Factor')
    plt.ylabel('Time on Air (ms)')
    plt.show()


if __name__ == '__main__':
    main()