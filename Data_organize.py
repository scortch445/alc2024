import sys


def read_lines(filename):
    with open(filename) as file:
        return file.readlines()


def writelines(filename, content):
    with open(filename, 'w') as file:
        file.writelines(content)


def gps_data(lines):
    gps_lines = []
    for line in lines:
        original_line = line
        line = line.strip().split(",")
        if '$GPGGA' in line:
            gps_lines.append(original_line)
    return gps_lines


def last_line(gps_lines):
    last_location = gps_lines[-1]
    return str(last_location)


def parse_gps_data(data):
    parts = data.split(',')
    if len(parts) < 14:
        return "Invalid GPS data"

    # Extracting individual fields
    fix_time = parts[1][:2] + ":" + parts[1][2:4] + ":" + parts[1][4:6]
    latitude = parts[2][:2] + "°" + parts[2][2:] + "'" + parts[3]
    longitude = parts[4][:3] + "°" + parts[4][3:] + "'" + parts[5]
    fix_quality = int(parts[6])
    num_satellites = int(parts[7])
    horizontal_dilution = float(parts[8])
    altitude = float(parts[9])
    height_geoid = float(parts[11])

    # Constructing readable information
    info = f"Fix time: {fix_time}\n"
    info += f"Latitude: {latitude}\n"
    info += f"Longitude: {longitude}\n"
    info += f"Fix quality: {fix_quality}\n"
    info += f"Number of satellites: {num_satellites}\n"
    info += f"Horizontal dilution of position: {horizontal_dilution}\n"
    info += f"Altitude: {altitude} meters\n"
    info += f"Height of geoid: {height_geoid} meters"

    return info




def main(infile, output):
    lines = read_lines(infile)
    gps_lines = gps_data(lines)
    line = last_line(gps_lines)
    readable_info = parse_gps_data(line)
    print(readable_info)
    writelines(output, gps_lines)


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
