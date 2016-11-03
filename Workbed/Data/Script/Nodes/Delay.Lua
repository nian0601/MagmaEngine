--Begin_Box--
--[NodeData][Name:Delay]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:InMS][VarType:int]
--[OutputPin][Name:Out][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID pinIndex)
	--sleep(GetPinData(aCaller, "InMS"))
	ExecutePin("Out", aCaller, aTreeID);
end
