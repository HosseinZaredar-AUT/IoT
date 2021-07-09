import matplotlib.pyplot as plt
import re

def main():

    # ----------- SPECIFY THE FILES --------------
    filename_15 = '15-12-14-250.sca'  #Nodes = 15 
    filename_30 = '30-12-14-250.sca'  #Nodes = 30
    # --------------------------------------------
    
    # texts to look for in the files
    energyText = 'totalEnergyConsumed'
    numPacketsText = 'totalReceivedPackets'
    sentPacketsText = 'sentPackets'

    # opening the files
    f_15 = open(filename_15)
    f_30 = open(filename_30)
    content_15 = f_15.read()
    content_30 = f_30.read()

    # total energy consumed
    totalEnergyConsumed_15 = sum(findItemValues(content_15, energyText))
    totalEnergyConsumed_30 = sum(findItemValues(content_30, energyText))

    # total sent packets
    totalSentPackets_15 = sum(findItemValues(content_15, sentPacketsText))
    totalSentPackets_30 = sum(findItemValues(content_30, sentPacketsText))

    # total received packets
    totalReceivedPackets_15 = findItemValues(content_15, numPacketsText)[0]
    totalReceivedPackets_30 = findItemValues(content_30, numPacketsText)[0]
    
    # calculations
    receivedPacketsRatio_15 = totalReceivedPackets_15 / totalSentPackets_15
    receivedPacketsRatio_30 = totalReceivedPackets_30 / totalSentPackets_30
    energyConsumption_15 = totalEnergyConsumed_15 / totalReceivedPackets_15
    energyConsumption_30 = totalEnergyConsumed_30 / totalReceivedPackets_30

    print(receivedPacketsRatio_15, receivedPacketsRatio_30)
    
    # plotting
    plt.rcParams['figure.figsize'] = [12, 5]
    plt.rcParams['figure.dpi'] = 100

    plt.subplot(1, 2, 1)
    plt.plot([15, 30], [receivedPacketsRatio_15, receivedPacketsRatio_30])
    plt.scatter([15, 30], [receivedPacketsRatio_15, receivedPacketsRatio_30])
    plt.xlabel('Number of Nodes')
    plt.ylabel('Received Packets Ratio')

    plt.subplot(1, 2, 2)
    plt.plot([15, 30], [energyConsumption_15, energyConsumption_30], color='orange')
    plt.scatter([15, 30], [energyConsumption_15, energyConsumption_30], color='orange')
    plt.xlabel('Number of Nodes')
    plt.ylabel('Energy Consumption')

    plt.show()


# a function to find item values in 'sca' files
def findItemValues(content, itemText):
    values = []
    idxs = [m.start() for m in re.finditer(itemText, content)]
    for idx in idxs:
        startIdx = idx + len(itemText) + 1
        endIdx = content.find('\n', startIdx)
        values.append(float(content[startIdx: endIdx]))
    return values


if __name__ == '__main__':
    main()