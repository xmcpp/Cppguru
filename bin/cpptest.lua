local trigger = ScriptMonitorObject:new();
local bCheckValue = false;

trigger:setCheckFunctionName( "checkFun" );

function checkfun()
    return bCheckValue;
end;

function setValue()
    bCheckValue = true;
end;