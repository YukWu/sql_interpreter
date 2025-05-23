# SQL Lexer 使用文档

## 概述

`Lexer` 类是一个 SQL 词法分析器，能够将 SQL 语句字符串转换为 Token 列表。它支持基本的 SQL 语法元素，包括关键字、标识符、字符串字面量、数字字面量、操作符等。

## 主要特性

- **关键字识别**：自动识别 SQL 关键字（SELECT, FROM, WHERE, INSERT, CREATE 等）
- **数据类型支持**：支持字符串、数字、布尔值和 NULL 字面量
- **操作符支持**：支持比较操作符（=, !=, <, >, <=, >=）和算术操作符（+, -, *, /, %）
- **位置跟踪**：记录每个 Token 的行号和列号，便于错误报告
- **错误处理**：对无法识别的字符进行错误处理

## 使用方法

### 基本用法

```cpp
#include "lexer/lexer.h"

// 创建 Lexer 实例
std::string sql = "SELECT name FROM users WHERE id = 123;";
sql_interpreter::lexer::Lexer lexer(sql);

// 执行词法分析
std::vector<sql_interpreter::lexer::Token> tokens = lexer.tokenize();

// 处理 Token
for (const auto& token : tokens) {
    std::cout << token.toString() << std::endl;
}
```

### Token 类型

词法分析器识别以下类型的 Token：

#### 关键字
- `SELECT`, `FROM`, `WHERE`, `INSERT`, `INTO`, `VALUES`
- `CREATE`, `TABLE`, `AS`, `AND`, `OR`, `NOT`

#### 字面量
- `STRING_LITERAL`: 字符串字面量（单引号或双引号）
- `NUMERIC_LITERAL`: 数字字面量（整数或浮点数）
- `BOOLEAN_LITERAL`: 布尔字面量（true, false）
- `NULL_LITERAL`: NULL 字面量

#### 操作符
- 比较操作符：`=`, `!=`, `<>`, `<`, `>`, `<=`, `>=`
- 算术操作符：`+`, `-`, `*`, `/`, `%`

#### 分隔符和标点
- `LEFT_PAREN` (`(`), `RIGHT_PAREN` (`)`)
- `COMMA` (`,`), `SEMICOLON` (`;`), `DOT` (`.`)

#### 其他
- `IDENTIFIER`: 标识符（表名、列名等）
- `END_OF_FILE`: 文件结束标记
- `UNKNOWN`: 无法识别的 Token

## 示例

### 简单查询
```sql
SELECT name, age FROM users;
```

生成的 Token：
```
Token[SELECT, 'SELECT', L:1, C:1]
Token[IDENTIFIER, 'name' ('name'), L:1, C:8]
Token[COMMA, ',', L:1, C:12]
Token[IDENTIFIER, 'age' ('age'), L:1, C:14]
Token[FROM, 'FROM', L:1, C:18]
Token[IDENTIFIER, 'users' ('users'), L:1, C:23]
Token[SEMICOLON, ';', L:1, C:28]
Token[END_OF_FILE, '', L:1, C:29]
```

### 带条件的查询
```sql
SELECT * FROM products WHERE price >= 100.0 AND active = true;
```

### 插入语句
```sql
INSERT INTO users (name, age) VALUES ('Alice', 25);
```

### 创建表语句
```sql
CREATE TABLE orders (id INTEGER, total DOUBLE, status STRING);
```

## 实现细节

### 架构设计
- `Lexer` 类：主要的词法分析器类
- `Token` 结构体：表示单个词法单元
- `TokenType` 枚举：定义所有支持的 Token 类型

### 关键字处理
关键字通过静态映射表进行识别，不区分大小写：
```cpp
static const std::unordered_map<std::string, TokenType> keywords_;
```

### 字面量值存储
Token 的字面量值使用 `std::variant` 存储，支持多种数据类型：
```cpp
std::variant<std::string, double, bool, std::nullptr_t> literal;
```

## 注意事项

1. **大小写不敏感**：关键字识别不区分大小写
2. **字符串引号**：支持单引号和双引号字符串
3. **数字格式**：支持整数和浮点数（包含小数点）
4. **错误处理**：无法识别的字符会生成 `UNKNOWN` 类型的 Token

## 扩展性

如需添加新的关键字或操作符，只需：
1. 在 `TokenType` 枚举中添加新类型
2. 在 `keywords_` 映射表中添加对应关系（如果是关键字）
3. 在 `scanToken()` 方法中添加识别逻辑（如果是新操作符）
4. 在 `tokenTypeToString()` 函数中添加字符串转换
