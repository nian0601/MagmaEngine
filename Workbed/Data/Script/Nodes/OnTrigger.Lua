--Begin_Box--
--[NodeData][Name:OnTrigger]
--[InputPin][Name:In][VarType:impulse]
--[OutputPin][Name:Out][VarType:impulse]
--[OutputPin][Name:OnEnter][VarType:impulse]
--[OutputPin][Name:OnExit][VarType:impulse]
--End_Box--

function Prepare()
end

function Run(aCaller, aTreeID, pinIndex)
	RegisterCallback(aCaller, aTreeID, "TriggerOnEnter", "OnTriggerEnter")
	RegisterCallback(aCaller, aTreeID, "TriggerOnExit", "OnTriggerExit")

	ExecutePin("Out", aCaller, aTreeID);
end

function OnTriggerEnter(aCaller, aTreeID)
	ExecutePin("OnEnter", aCaller, aTreeID)
end

function OnTriggerExit(aCaller, aTreeID)
	ExecutePin("OnExit", aCaller, aTreeID)
end