--Begin_Box--
--[NodeData][Name:If]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:Flag][VarType:bool]
--[OutputPin][Name:Out][VarType:impulse]
--[OutputPin][Name:True][VarType:impulse]
--[OutputPin][Name:False][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID, pinIndex)
	flag = GetPinData(aCaller, aTreeID, "Flag")

	if(flag == true) then
		ExecutePin("True", aCaller, aTreeID);
	else
		ExecutePin("False", aCaller, aTreeID);
	end

	ExecutePin("Out", aCaller, aTreeID);
end
