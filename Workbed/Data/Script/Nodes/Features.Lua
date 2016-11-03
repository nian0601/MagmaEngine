--Begin_Box--
--[NodeData][Name:Features]
--[InputPin][Name:In][VarType:impulse]
--[InputPin][Name:ObjectID][VarType:int][Command:Name:Show_In_Unity,Path:GotoCommand.bat]
--[InputPin][Name:IntIn][VarType:int]
--[InputPin][Name:FloatIn][VarType:float]
--[InputPin][Name:BoolIn][VarType:bool]
--[InputPin][Name:PointerIn][VarType:pointer]
--[InputPin][Name:StringIn][VarType:string]
--[OutputPin][Name:OutInt][VarType:int]
--[OutputPin][Name:OutFloat][VarType:float]
--[OutputPin][Name:OutBool][VarType:bool]
--[OutputPin][Name:OutPointer][VarType:pointer]
--[OutputPin][Name:OutString][VarType:string]
--End_Box--

function Prepare()
end

function Run(aCaller, pinIndex)
	ExecutePin("Out", aCaller);
end
