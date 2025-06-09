def get_time_to_millisec(time_str):
    return (int(time_str[:2]) * 3600 + int(time_str[3:5]) * 60 + int(time_str[6:8])) * 1000 + int(time_str[9:])

def solution(lines):
    times = []
    max_throughput = 0
    
    for line in lines:
        _, end_time, duration = line.split()
        end = get_time_to_millisec(end_time)
        start = end - int(float(duration[:-1]) * 1000) + 1
        times.append((start, end))
        
    for _, end in times:
        count = sum(1 for start, t_end in times if start <= end + 999 and t_end >= end)
        max_throughput = max(max_throughput, count)
    
    return max_throughput