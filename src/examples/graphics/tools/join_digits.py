import sys


def join_digits(lhs,rhs):
    
    lhs_file = "digit_" + str(lhs) + ".txt"
    rhs_file = "digit_" + str(rhs) + ".txt"
    
    output_file = "shape_" + str(lhs) + str(rhs) + ".txt"
    
    iLhsFile = open(lhs_file)
 
    lhs = []
    lhsLength = 0
    for lhsLine in iLhsFile:
        
        lhs.append(lhsLine)
        lhsLength+=1
    
    iLhsFile.close()

    iRhsFile = open(rhs_file)

    rhs = []
    rhsLength = 0
    for rhsLine in iRhsFile:
        
        rhs.append(rhsLine)
        rhsLength+=1

    iRhsFile.close()
    
    oFile = open(output_file,'w')

    for counter in range(0,max(lhsLength,rhsLength)):
        oFile.write(lhs[counter].strip()+rhs[counter])
    oFile.close() 


if __name__ == "__main__":
    start = int(sys.argv[1])
    end   = int(sys.argv[2])
    
    for number in range(start,end+1):
        lhs = number // 10
        rhs = number % 10
        print(f"lhs: {lhs}")
        print(f"rhs: {rhs}")
        join_digits(lhs,rhs)
