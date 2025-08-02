# 使用内置字典作为哈希表
hash_table = {}

# 插入
hash_table["apple"] = 5
hash_table["banana"] = 8
hash_table["orange"] = 3

# 查找
print(hash_table.get("apple"))  # 输出: 5

# 删除
del hash_table["banana"]

# 验证删除
print(hash_table.get("banana"))  # 输出: None

# 遍历
for key, value in hash_table.items():
    print(f"{key}: {value}")
