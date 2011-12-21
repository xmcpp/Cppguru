local trigger = ScriptMonitorObject:new();
local bCheckValue = false;

trigger:enable(true);
trigger:setCheckFunctionName( "fun.checkFun" );
fun = {};

function fun.checkFun()
    return bCheckValue;
end;

function setValue()
    bCheckValue = true;
end;

function checkAlarm()
    return trigger:isAlarmed();
end;