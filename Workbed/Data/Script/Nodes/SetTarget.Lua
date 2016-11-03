--Begin_Box--
--[NodeData][Name:SetTarget]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:Target][VarType:int]
--[OutputPin][Name:Out][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID, pinIndex)
	SetTarget(aCaller, aTreeID, GetPinData(aCaller, aTreeID, "Target"))
	ExecutePin("Out", aCaller, aTreeID);
end