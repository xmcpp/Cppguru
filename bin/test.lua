local value = false;

--�����Ƿ���Ե����޷���ֵ,�޲���ĺ���
function setBoolValue()
	value = true;
end;

--���Ծֲ�����value�Ƿ���ȷ����
function getBoolValue()
    return value;
end;

--�����Ƿ���Ե��÷���ֵ�ĺ���
function getIntValue()
    return 1;
end;

--�����Ƿ���Ե��ñ��еĺ���
a = {};
function a.b()
    value = true;
end;