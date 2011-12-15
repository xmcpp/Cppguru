local value = false;

--测试是否可以调用无返回值,无残书的函数
function setBoolValue()
	value = true;
end;

--测试局部变量value是否被正确设置
function getBoolValue()
    return value;
end;

--测试是否可以调用返回值的函数
function getIntValue()
    return 1;
end;

--测试是否可以调用表中的函数
a = {};
function a.b()
    value = true;
end;

--测试嵌套表
c = {};

function c.f()
    value = true;
end;

z = { b = c };
