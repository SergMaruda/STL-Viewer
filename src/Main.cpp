#include <iostream>

#include <STEPControl_Reader.hxx>
#include "IFSelect_SignatureList.hxx"
#include <TColStd_SequenceOfTransient.hxx>
#include <TColStd_HSequenceOfTransient.hxx>

#include <Interface_InterfaceModel.hxx>
#include <Interface_EntityIterator.hxx>
#include <TopoDS_Shape.hxx>
#include <TColStd_HSequenceOfTransient.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <XSControl_WorkSession.hxx>
#include <Transfer_TransientProcess.hxx>
#include <TopoDS_Iterator.hxx> 
#include <StepData_StepModel.hxx> 
#include <set>

#include <map>
#include <TopExp_Explorer.hxx>

#include <Geom_Surface.hxx>
#include <Geom_Point.hxx>
#include <StepGeom_ConicalSurface.hxx>
#include <StepGeom_Plane.hxx>
#include <StepGeom_CylindricalSurface.hxx>
#include <BRep_Builder.hxx>
#include <StepToGeom_MakeSurface.hxx>
#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>
#include <StepGeom_Placement.hxx>
#include <GeomTools_SurfaceSet.hxx>

IFSelect_ReturnStatus ReadSTEP(const Standard_CString& aFileName,
	Handle(TopTools_HSequenceOfShape)& aHSequenceOfShape)
{
	aHSequenceOfShape->Clear();

	// create additional log file
	STEPControl_Reader aReader;
	IFSelect_ReturnStatus status = aReader.ReadFile(aFileName);
	if (status != IFSelect_RetDone)
		return status;
	
	aReader.WS()->MapReader()->SetTraceLevel(2); // increase default trace level

	auto model = aReader.StepModel();

	auto num = model->NbEntities();


	std::set<std::string> diff_types;


	std::set<Handle(StepGeom_Plane)> planes;

	std::set<Handle(StepGeom_Surface)> surfaces;

	std::set<Handle(StepGeom_CylindricalSurface)> cylinders;

	std::set<Handle(Geom_Point)> points;

	std::set<Handle(StepGeom_Placement)> axes;

	std::map<std::string, size_t> num_types;

	for(Standard_Integer i = 1; i <=num; ++i)
	{
		auto ent = model->Entity(i);
		auto plane = Handle(StepGeom_Plane)::DownCast (ent );

		if(plane)
			planes.insert(plane);
		else
		{
			auto p_cyl = Handle(StepGeom_CylindricalSurface)::DownCast (ent );
			if(p_cyl)
			{
			cylinders.insert(p_cyl);

			Handle(Geom_Surface) res;
			StepToGeom_MakeSurface::Convert(p_cyl, res);

			GeomTools_SurfaceSet::PrintSurface(res,std::cout);
			}
			else
			{
			auto surfs = Handle(StepGeom_Surface)::DownCast (ent );
			if(surfs)
				{
				surfaces.insert(surfs);
				}
				else
				{
				auto p_axis = Handle(StepGeom_Placement)::DownCast (ent );
				if(p_axis)
					axes.insert(p_axis );
     			}
			}


		}


		auto dn_t = ent->DynamicType();
		//std::cout<<"name: " <<dn_t->Name()<<"\n";
		diff_types.insert(dn_t->Name());

		++num_types[dn_t->Name()];
	}

	return status;
}


int main( int arc, char **  argv) 
{
	std::cout<<"STEP Files Analyzer\n";

	const char* file_name = "C:\\Users\\Sergey\\Desktop\\TASK\\impeller1.stp";

	Handle(TopTools_HSequenceOfShape) aSequence= new TopTools_HSequenceOfShape();

	auto res = ReadSTEP(file_name, aSequence);

	return 0;
}
