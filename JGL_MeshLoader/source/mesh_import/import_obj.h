#pragma once

#include "import_base.h"

namespace nmesh_import {

	class ObjMeshImporter : public IMeshImporter
	{
	public:
		virtual bool from_file(const std::string& filepath, nelems::Mesh* pMesh) override;

	};
}
