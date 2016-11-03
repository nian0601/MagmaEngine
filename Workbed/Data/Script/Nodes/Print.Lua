--Begin_Box--
--[NodeData][Name:Print]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:In2][VarType:string]
--[OutputPin][Name:Out][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID, pinIndex)
	PrintToScreen(GetPinData(aCaller, aTreeID, "In2"));	
	ExecutePin("Out", aCaller, aTreeID);
end
