local trigger = ScriptMonitorObject:new();
local bCheckValue = false;

trigger:enable(true);
trigger:setCheckFunctionName( "checkFun" );

function checkFun()
    return bCheckValue;
end;

function setValue()
    bCheckValue = true;
end;

function checkAlarm()
    return trigger:isAlarmed();
end;