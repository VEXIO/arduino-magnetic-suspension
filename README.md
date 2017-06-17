## Arduino Magnetic Suspension

#### Todo list
1. 小车检测模块（红外LED发射接收管->阻断传感器）->小车位置
2. 根据位置与启动状态控制电磁铁通断（可能不能反向）->8路继电器
3. 速度显示（4位7段数码管）
4. 启动开关（按钮，去抖动）

#### Workflow
```c
// global variables
// use global variables to communicate

void loop(){
	checkCarStatus(); // 更新小车位置
	calculateSpeed(); // 计算小车速度
	checkBtnStatus(); // 更新按钮状态
	show47digit(); // 更新数码管显示
	changePower(); // 继电器
}
```



```flow
st=>start: Start
op1=>operation: 磁悬浮车在轨道上运行
op2=>operation: 磁悬浮车前方为N级，后方为S级
op3=>operation: 启动
op4=>operation: 小车前方电磁铁磁铁置为前S后N
op5=>operation: 运行
cond1=>condition: 前进时经过红外传感器?
cond1yes=>operation: 小车前方的电磁铁反向（考虑自感延迟所以提前反向）
cond2=>condition: 到达轨道尾部？
e=>end: 结束运行

st->op1->op2->op3->op4->op5->cond1
cond1yes->cond2
cond1(yes)->cond1yes
cond1(no)->op5
cond2(yes)->e
cond2(no)->op5
```

