
#ifndef _MRenderUtil
#define _MRenderUtil
//
//-
// ==========================================================================
// Copyright (C) Alias Systems Corp., and/or its licensors ("Alias").  
// All rights reserved.  These coded instructions, statements, computer  
// programs, and/or related material (collectively, the "Material")
// contain unpublished information proprietary to Alias, which is
// protected by Canadian and US federal copyright law and by international
// treaties. This Material may not be disclosed to third parties, or be copied
// or duplicated, in whole or in part, without the prior written consent of
// Alias.  ALIAS HEREBY DISCLAIMS ALL WARRANTIES RELATING TO THE MATERIAL,
// INCLUDING, WITHOUT LIMITATION, ANY AND ALL EXPRESS OR IMPLIED WARRANTIES OF
// NON-INFRINGEMENT, MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
// IN NO EVENT SHALL ALIAS BE LIABLE FOR ANY DAMAGES WHATSOEVER, WHETHER DIRECT,
// INDIRECT, SPECIAL, OR PUNITIVE, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, OR IN EQUITY, ARISING OUT OF OR RELATED TO THE
// ACCESS TO, USE OF, OR RELIANCE UPON THE MATERIAL.
// ==========================================================================
//+
//
// CLASS:    MRenderUtil
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MRenderUtil)
//
// MRenderUtil is a static class which provides access to Maya's rendering
// functionalities
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES


#include <maya/MStatus.h>
#include <maya/MTypes.h>

// *****************************************************************************

// DECLARATIONS

class MFloat;
class MFloatPoint;
class MFloatVector;
class MFloatVectorArray;
class MIntArray;
class MFloatPoint;
class MFloatArray;
class MFloatPointArray;
class MFloatMatrix;
class MObject;
class MString;

// *****************************************************************************

// CLASS DECLARATION (MRenderUtil)

/// Static class providing common API rendering functions (OpenMayaRender)
/**
*/
class OPENMAYARENDER_EXPORT MRenderUtil
{
public:

	///
	enum MRenderState {
		/// Maya is not currently rendering
		kNotRendering,
		/// Maya is performing a batch render
		kBatchRender,
		/// Maya is performing an interactive render
		kInteractiveRender,
		/// Maya is performing an IPR render
		kIprRender,
		/// Maya is performing a hardware render
		kHardwareRender
	};

	///
	enum MRenderPass {
		/// Default case
		kAll,
		/// Only the color information is being computed, no shadows
		kColorOnly,
		/// Only the shadow information is being computed, no color
		kShadowOnly,
		/// Only the specular information is being computed
		kAmbientOnly,
		/// Only the specular information is being computed
		kDiffuseOnly,
		/// Only the specular information is being computed
		kSpecularOnly
	};

	///
	static MRenderState	mayaRenderState();

	///
	static MStatus	raytrace(
						const MFloatVector& rayOrigin,  // in camera space
						const MFloatVector& rayDirection,
						const int objectId,
						const int raySampler,
						const short rayDepth,

						// storage for return value

						MFloatVector& resultColor,
						MFloatVector& resultTransparency,

						// true for reflected rays, false for refracted rays
						const bool isReflectedRays = true
					);

	// vectorized version

	///
	static MStatus	raytrace(
						const MFloatVectorArray& rayOrigins,  // in camera space
						const MFloatVectorArray& rayDirections,
						const int objectId,
						const int raySampler,
						const short rayDepth,

						// storage for return value

						MFloatVectorArray& resultColors,
						MFloatVectorArray& resultTransparencies,

						// true for reflected rays, false for refracted rays
						const bool isReflectedRays = true
					);

	///
	static MStatus	raytraceFirstGeometryIntersections(
						const MFloatVectorArray& rayOrigins,  // in camera space
						const MFloatVectorArray& rayDirections,
						const int objectId,
						const int raySampler,

						// storage for return value

						MFloatVectorArray& 	resultIntersections,
						MIntArray& 			resultIntersected
					);


	///
	static MStatus sampleShadingNetwork(

		MString             shadingNodeName,
		int                numSamples,
		bool				useShadowMaps,
		bool				reuseMaps,

		MFloatMatrix		&cameraMatrix,	// eye to world

		MFloatPointArray    *points,	// in world space
		MFloatArray         *uCoords,
		MFloatArray         *vCoords,
		MFloatVectorArray   *normals,	// in world space
		MFloatPointArray    *refPoints,	// in world space
		MFloatVectorArray   *tangentUs,	// in world space
		MFloatVectorArray   *tangentVs,	// in world space
		MFloatArray         *filterSizes,

		MFloatVectorArray   &resultColors,
		MFloatVectorArray   &resultTransparencies
	);

	///
	static bool 	   generatingIprFile();

	///
	static bool exactFileTextureName(
						const MObject& fileNode,
						MString& texturePath,
						MStatus *ReturnStatus = NULL
					);
	///
	static bool exactFileTextureName(
						const MString& baseName,
						bool           useFrameExt,
						const MString& currentFrameExt,
						MString&       exactName,
						MStatus *ReturnStatus = NULL
						);

	///
	static MString relativeFileName(
						const MString& absFileName,
						MStatus *ReturnStatus = NULL
						);

	/// Internal use only
	static bool convertPsdFile(
						const MObject& fileNode,
						MString& texturePath,
						const bool		&state = false,
						MStatus *ReturnStatus = NULL
					);

	///
	static bool exactImagePlaneFileName(
						const MObject& imagePlaneNode,
						MString& texturePath,
						MStatus *ReturnStatus = NULL
					);

	///
	static MRenderPass renderPass( void );

	/// 
	static float	diffuseReflectance(
						int lightBlindData,
						const MFloatVector& lightDirection,
						const MFloatVector& pointCamera,
						const MFloatVector& normal,
						bool lightBackFace,
						MStatus *ReturnStatus = NULL );

	/// 
	static MFloatVector		maximumSpecularReflection(
								int lightBlindData,
								const MFloatVector& lightDirection,
								const MFloatVector&  pointCamera,
								const MFloatVector& normal,
								const MFloatVector& rayDirection,
								MStatus *ReturnStatus = NULL );

 	/// 
	static float	lightAttenuation(
							int lightBlindData,
							const MFloatVector& pointCamera,
							const MFloatVector& normal,
							bool lightBackFace,
							MStatus *ReturnStatus = NULL );

	/// 
	static float	hemisphereCoverage(
							int lightBlindData,
							const MFloatVector& lightDirection,
							const MFloatVector& pointCamera,
							const MFloatVector& rayDirection,
							bool lightBackFace,
							MStatus *ReturnStatus = NULL );
	
	///
	static void		sendRenderProgressInfo (MString &pixFile, int percentageDone);


protected:
	static const char* className();
private:
    ~MRenderUtil();
#ifdef __GNUC__
	friend class shutUpAboutPrivateDestructors;
#endif
};

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MRenderUtil */
