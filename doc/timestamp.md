# Timestamp
`Timestamp` 唯一的成员变量 `microSecondsSinceEpoch` 是以微秒的形式记录了 
`unix` 时钟走过的时间。其所有成员方法都是得这一变量的操作：
+ `now()`: 通过获取当前时间，并将其转换为 `Timestamp` 形式。
+ `toFormattedString()`: 将 `microSecondsSinceEpoch_` 以年月日的形式输出。