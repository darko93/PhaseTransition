def SaveLinesToFile(lines, filePath):
    with open(filePath, "w") as file:
        for line in lines:
            file.write(line)