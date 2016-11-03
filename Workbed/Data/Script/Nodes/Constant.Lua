--Begin_Box--
--[NodeData][Name:Constant]
--[InputPin][Name:TheData][VarType:int]
--[OutputPin][Name:Out][VarType:int]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID, pinIndex)
	--PrintLog(aCaller, GetPinData(aCaller, "In2"));	
	ExecutePin("Out", aCaller, aTreeID);
end
