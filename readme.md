# Tính năng
- Thư viện header cho C++, được viết với cú pháp gần giống với C#.
- Sẽ được cập nhật thường xuyên.
- Góp ý chỉnh sửa, vấn đề về lỗi:
- https://docs.google.com/spreadsheets/d/1daUnzLGA25gMm7cQyPbCJFuH5yH6oa1xkdywSWb6cQo/edit?usp=sharing

### Cách sử dụng:
- Gọi: &lt;tên namespace&gt;::&lt;tên class (nếu có)&gt;::&lt;tên hàm&gt;
- Có thể gán biến nếu hàm có giá trị trả về.

### Cập nhật sắp tới
- Thêm chú thích cách sử dụng các hàm.
- Chia ra 2 file .h và .cpp, không cần phải đặt tùy chọn Linker /FORCE:MULTIPLE trong Visual Studio.

### Cập nhật 29/3/2022
- Sửa đổi tham số hàm String::Insert().

### Cập nhật 8/3/2022
- Thêm Namespace String: Replace().

### Cập nhật 6/3/2022
- Xóa hàm trong Namespace File: SaveClass(), ReadClassList().

### Cập nhật 24/2/2022
- Thêm Namespace Custom: GetCmdOutput().
- Thêm Namespace File: WriteLine().

### Cập nhật 21/2/2022
- Thêm Namespace File: SaveClass(), ReadClassList().

### Cập nhật 16/2/2022
- Thêm Class DateTime: DateTime(+3 overload), Now(), ToString(), ShortDay(), LongDay().
- Thêm Namespace LongLong: Parse(), TryParse().
- Namespace String: Parse(+3 overload), Insert().
- Namespace Double: TryParse().
- Namespace Int: TryParse().

### Cập nhật 15/2/2022
- Namespace Custom: GetType(), Min(), Max().
- Namespace String: Parse(+2 overload), Split(), Sort().
- Namespace Double: Parse().
- Namespace Int: Parse().
- Namespace File: ReadFile(), WriteFile(), WriteFileMulti().
