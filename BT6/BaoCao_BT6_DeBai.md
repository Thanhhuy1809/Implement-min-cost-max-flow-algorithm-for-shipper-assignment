# BÀI TẬP 6 — Tổng hợp 3 Bài toán Luồng trên Đồ thị

> Nguồn: [BT8.pdf](file:///c:/hehe/Chuyende2/BT6/BT8.pdf)

---

## Bài toán 1: Phân phối Vắc-xin

### Đề bài

Cho một mạng gồm:
- **N** nút (kho, trạm, và/hoặc nút trung gian)
- **M** cạnh có hướng với **sức chứa (capacity)** thể hiện giới hạn vận chuyển trên mỗi tuyến đường
- **W** kho với lượng vắc-xin khả dụng (supply)
- **C** trạm y tế với nhu cầu (demand)

Hãy tính lượng vắc-xin tối đa giao được từ các kho đến các trạm theo ràng buộc sức chứa các tuyến đường.

### Định dạng vào/ra

**Input:**
- Dòng đầu: 4 số `N M W C`
- Dòng 2: `W` cặp số nguyên — mỗi cặp gồm **ID nút của kho** và **lượng vắc-xin có thể cung cấp**
- Dòng 3: `C` cặp số nguyên — mỗi cặp gồm **ID nút của trạm y tế** và **nhu cầu của trạm**
- `M` dòng tiếp: mỗi dòng gồm 3 số `u v z` — đường nối từ nút `u` đến nút `v` có dung lượng vận chuyển tối đa là `z`

**Output:**
- Dòng đầu: `T` là tổng lượng vắc-xin có thể cung cấp
- In `"YES"` nếu T ≥ tổng nhu cầu (đáp ứng đủ), ngược lại in `"NO"`

**Gợi ý:** Tạo 2 đỉnh giả — siêu nguồn (tổng lượng cung cấp) và siêu đích (tổng lượng nhu cầu).

### Ví dụ

| # | Input | Output |
|---|---|---|
| 1 | `4 4 2 2` / `1 5  2 7` / `3 4  4 6` / `1 3 3` / `1 4 2` / `2 3 1` / `2 4 6` | `10` / `YES` |
| 2 | `2 0 1 1` / `1 5` / `2 5` | `0` / `NO` |
| 3 | `6 6 3 3` / `1 4  2 6  3 3` / `4 2  5 4  6 5` / `1 4 3` / `1 5 1` / `2 4 2` / `2 5 3` / `2 6 2` / `3 6 3` | `11` / `YES` |
| 4 | `6 7 2 2` / `1 8  2 5` / `5 6  6 6` / `1 3 5` / `1 4 3` / `2 4 5` / `3 5 4` / `3 6 2` / `4 5 3` / `4 6 4` | `12` / `YES` |
| 5 | `4 4 2 2` / `1 5  2 7` / `3 4  4 6` / `1 3 2` / `1 4 1` / `2 3 1` / `2 4 4` | `8` / `NO` |

---

## Bài toán 2: Định tuyến để đạt Băng thông Tối đa trên Mạng

### Đề bài

Quản lý một mạng định tuyến có **N** nút và **M** cạnh có hướng. Mỗi cạnh `(u→v)` có dung lượng `c` biểu diễn **băng thông tối đa** (số bits truyền qua trong một đơn vị thời gian).

Cho 2 nút đặc biệt:
- **Nguồn `s`** (data center nguồn)
- **Đích `t`** (data center đích)

**Nhiệm vụ:**
1. Tính **tổng băng thông tối đa** có thể route từ `s` đến `t` (luồng cực đại)
2. *(Tùy chọn)* Xuất các **phân luồng theo đường đi** (path decomposition) — chia luồng cực đại thành các tuyến đơn giản từ `s` đến `t` kèm lưu lượng trên mỗi tuyến

### Định dạng vào/ra

**Input:**
- Dòng đầu: 4 số `N M s t`
- `M` dòng tiếp: mỗi dòng gồm 3 số `u v c`

**Output:**
- Dòng đầu: tổng luồng cực đại `T`
- *(Tùy chọn)* Dòng 2: số lượng phân luồng `K`
- *(Tùy chọn)* `K` dòng tiếp: mỗi dòng gồm `Fk` (lưu lượng), `Lk` (số nút trên tuyến), và `Lk` số ID nút trên tuyến

### Ví dụ

**Ví dụ 1:**
```
Input:                    Output:
5 6 1 5                   4
1 2 3                     2
1 3 2                     2 4 1 2 4 5
2 3 1                     2 4 1 3 4 5
2 4 2
3 4 3
4 5 4
```
> **Giải thích:** Luồng tối đa = 4 (bão hòa cạnh 4→5). Phân luồng: 2 đơn vị qua 1→2→4→5 và 2 đơn vị qua 1→3→4→5.

**Ví dụ 2:**
```
Input:                    Output:
6 7 1 6                   4
1 2 2                     3
1 3 2                     1 4 1 2 4 6
2 4 1                     1 4 1 2 5 6
2 5 1                     2 4 1 3 5 6
3 5 2
4 6 1
5 6 3
```
> **Giải thích:** Tổng vào đích tối đa = 4 (1 qua 4→6, 3 qua 5→6). Phân luồng gồm 3 tuyến.

---

## Bài toán 3: Điều phối Xe cứu thương

### Đề bài

Quản lý một thành phố có:
- **Đồ thị đường:** N nút giao, M cạnh (mỗi cạnh có thời gian di chuyển)
- **A** xe cứu thương (mỗi xe đứng tại một nút)
- **P** hiện trường (mỗi hiện trường là một ca cấp cứu tại một nút, có **thời gian tối đa cho phép** để xe đến)

**Ràng buộc:**
- Một xe chỉ nhận **tối đa 1 ca**
- Mỗi ca chỉ cần **1 xe**

**Yêu cầu:** Tính số ca tối đa có thể cứu kịp và xuất ghép cặp xe–ca.

### Định dạng vào/ra

**Input:**
- Dòng đầu: 4 số `N M A P`
- `A` dòng tiếp: mỗi dòng là vị trí (ID nút) của xe cứu thương
- `P` dòng tiếp: mỗi dòng gồm 2 số — vị trí hiện trường (ID nút) và thời gian tối đa cho phép
- `M` dòng tiếp: mỗi dòng gồm 3 số `u v t` — tuyến đường giữa nút `u` và `v` có thời gian di chuyển `t`

**Output:**
- Dòng đầu: số `K` — số ca cấp cứu tối đa đáp ứng được
- `K` dòng tiếp: mỗi dòng gồm cặp `ID_xe  ID_hiện_trường`

### Ví dụ

**Ví dụ 1:**
```
Input:                    Output:
6 7 2 3                   2
1                         2 2
6                         1 1
3 4
5 5
2 2
1 2 1
2 3 2
3 4 2
4 5 1
5 6 2
2 5 3
1 6 10
```

**Ví dụ 2:**
```
Input:                    Output:
4 2 1 2                   0
1
3 2
4 1
1 2 5
3 4 5
```

**Ví dụ 3:**
```
Input:                    Output:
5 6 3 3                   3
1                         1 1
2                         2 3
5                         3 2
3 2
4 3
2 3
1 2 1
2 3 1
3 4 1
4 5 1
1 3 3
2 5 4
```

---

## Tổng kết phân loại bài toán

| # | Bài toán | Loại thuật toán | Mô hình |
|---|---|---|---|
| 1 | Phân phối Vắc-xin | **Max-Flow** (nhiều nguồn, nhiều đích) | Siêu nguồn/siêu đích + Ford-Fulkerson/Edmonds-Karp |
| 2 | Băng thông tối đa | **Max-Flow** + Path Decomposition | Ford-Fulkerson/Edmonds-Karp + DFS phân luồng |
| 3 | Điều phối Xe cứu thương | **Dijkstra** + **Maximum Bipartite Matching** | Đường đi ngắn nhất + Hopcroft-Karp/Hungarian |

### Yêu cầu cho mỗi bài toán:

1. ✏️ Tìm và phân tích giải thuật để giải quyết bài toán
2. 📊 Vẽ lưu đồ thuật toán của giải thuật chính
3. ⚖️ So sánh các giải pháp (ngôn ngữ lập trình, giải thuật khác nhau, ...)
