import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('/Users/tainewang/Desktop/大三/Program Design/HW10/clock_delete.csv')
df = pd.DataFrame(data)

stats = df['clock cycles'].describe()

print(stats)

# 分組區間
bins = list(range(200, 7000, 400))

# 將數據分組並計算頻率
df['bins'] = pd.cut(df['clock cycles'], bins=bins, right=False)  # 分組
frequency = df['bins'].value_counts(sort=False)  # 統計頻率
bin_labels = [f"{int(interval.left)}-{int(interval.right)}" for interval in frequency.index]  # 區間標籤

plt.figure(figsize=(12, 6))
plt.plot(range(len(frequency)), frequency.values, marker='o', color='blue', linestyle='-')

plt.xticks(range(len(frequency)), bin_labels, rotation=45, fontsize=10)

plt.title('Function 6 prefix_delete(...)', fontsize=16)
plt.xlabel('Clock Cycles', fontsize=12)
plt.ylabel('Frequency', fontsize=12)

plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()
