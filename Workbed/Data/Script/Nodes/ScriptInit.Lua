--Begin_Box--
--[NodeData][Name:Script Init][IsInitNode:1]
--[OutputPin][Name:Start][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID, pinIndex)
	ExecutePin("Start", aCaller, aTreeID);
end
