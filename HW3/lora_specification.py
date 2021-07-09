from tabulate import tabulate
import math

def main():
    
    # Table headers
    headers = ['SF', 'Bit rate (kb/s)', 'Sensitivity (dbm)', 'ToA (ms)', 'SNR (dbm)']

    # Spread Factor (SF)
    sfs = [7, 8, 9, 10, 11, 12]

    # Bandwidth
    bws = [125_000, 250_000, 500_000]

    cr = 4/5      # Coding Rate
    snr0 = 31     # SNR0
    payload = 14  # payload size (bytes)
    
    for bw in bws:

        table = []

        for sf in sfs:

            bitrate = ((bw / (2 ** sf)) * sf * cr) / 1000

            snr = 10 * math.log10(snr0 / (2 ** sf))
            rec_sens = -174 + 6 + 10 * math.log10(bw) + snr

            n_preample = 8
            n_payload = 8 + max(math.ceil((8 * payload - 4 * sf + 28 + 16) / (4 * (sf - 2))) * (1 + 4), 0)
            t_on_air = ((n_payload + (n_preample + 4.25)) * ((2 ** sf) / bw)) * 1000

            row = [sf, bitrate, rec_sens, t_on_air, snr]
            table.append(row)

        print(f'Bandwidth = {int(bw/1000)}kHz', )
        print(tabulate(table, headers, tablefmt="fancy_grid"))
        print()


if __name__ == '__main__':
    main()