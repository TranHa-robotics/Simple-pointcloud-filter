import numpy as np
import time

# 1. Sinh 1 triệu điểm ngẫu nhiên trong khoảng không gian 10x10x10 mét
print("Đang tạo dữ liệu...")
start_time = time.time()
points = np.random.uniform(0.0, 10.0, (1000000, 3))

# 2. Ghi ra file text format xyz
output_file = "1m_points.txt"
np.savetxt(output_file, points, fmt='%.6f')

print(f"Đã lưu 1 triệu điểm vào {output_file} trong {time.time() - start_time:.2f} giây.")