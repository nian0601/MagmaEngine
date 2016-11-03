--Begin_Box--
--[NodeData][Name:Splitter]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:In2][VarType:impulse]
--[OutputPin][Name:Out][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID, pinIndex)
	ExecutePin("Out", aCaller, aTreeID);
end
