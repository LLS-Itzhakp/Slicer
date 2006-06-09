/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkMRMLVolumeNode.h,v $
  Date:      $Date: 2006/03/19 17:12:29 $
  Version:   $Revision: 1.13 $

=========================================================================auto=*/
// .NAME vtkMRMLVolumeNode - MRML node for representing a volume (image stack).
// .SECTION Description
// Volume nodes describe data sets that can be thought of as stacks of 2D 
// images that form a 3D volume.  Volume nodes describe where the images 
// are stored on disk, how to render the data (window and level), and how 
// to read the files.  This information is extracted from the image 
// headers (if they exist) at the time the MRML file is generated.  
// Consequently, MRML files isolate MRML browsers from understanding how 
// to read the myriad of file formats for medical data. 

#ifndef __vtkMRMLVolumeNode_h
#define __vtkMRMLVolumeNode_h

#include "vtkMatrix4x4.h"
#include "vtkImageData.h"

#include "vtkMRML.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLStorageNode.h"
#include "vtkMRMLVolumeDisplayNode.h"
#include "vtkMRMLTransformNode.h"

class vtkImageData;

class VTK_MRML_EXPORT vtkMRMLVolumeNode : public vtkMRMLNode
{
  public:
  static vtkMRMLVolumeNode *New(){return NULL;};
  vtkTypeMacro(vtkMRMLVolumeNode,vtkMRMLNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance() = 0;

  // Description:
  // Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  // Description:
  // Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  // Description:
  // Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  // Description:
  // Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() = 0;

  // Description:
  // Finds the storage node and read the data
  virtual void UpdateScene(vtkMRMLScene *scene);


  //--------------------------------------------------------------------------
  // RAS->IJK Matrix Calculation
  //--------------------------------------------------------------------------

  // Description:
  // The order of slices in the volume. One of: LR (left-to-right), 
  // RL, AP, PA, IS, SI. This information is encoded in the rasToIJKMatrix.
  // This matrix can be computed either from corner points, or just he
  // scanOrder.
  static void ComputeIJKToRASFromScanOrder(char *order, vtkMatrix4x4 *IJKToRAS);
  static const char* ComputeScanOrderFromIJKToRAS(vtkMatrix4x4 *IJKToRAS);

  void SetIJKToRASDirections(double dirs[3][3]);
  void SetIJKToRASDirections(double ir, double ia, double is,
                             double jr, double ja, double js,
                             double kr, double ka, double ks);
  void SetIToRASDirection(double ir, double ia, double is);
  void SetJToRASDirection(double jr, double ja, double js);
  void SetKToRASDirection(double kr, double ka, double ks);

  void GetIJKToRASDirections(double dirs[3][3]);
  void GetIToRASDirection(double dirs[3]);
  void GetJToRASDirection(double dirs[3]);
  void GetKToRASDirection(double dirs[3]);

  // Description:
  // Spacing and Origin, with the Directions, are the independent
  // parameters that go to make up the IJKToRAS matrix
  vtkGetVector3Macro (Spacing, double);
  vtkSetVector3Macro (Spacing, double);
  vtkGetVector3Macro (Origin, double);
  vtkSetVector3Macro (Origin, double);

  // Description:
  // Get the IJKToRAS Matrix that includes the spacing and origin
  // information (assumes the image data is Origin 0 0 0 and Spacing 1 1 1)
  // RASToIJK is the inverse of this
  void GetIJKToRASMatrix(vtkMatrix4x4* mat);
  void GetRASToIJKMatrix(vtkMatrix4x4* mat);

  // Description:
  // Convenience methods to set the directions, spacing, and origin 
  // from a matrix
  void SetIJKToRASMatrix(vtkMatrix4x4* mat);
  void SetRASToIJKMatrix(vtkMatrix4x4* mat);

  // Description:
  // String ID of the storage MRML node
  vtkSetStringMacro(StorageNodeID);
  vtkGetStringMacro(StorageNodeID);

  // Description:
  // String ID of the display MRML node
  vtkSetStringMacro(DisplayNodeID);
  vtkGetStringMacro(DisplayNodeID);

  // Description:
  // String ID of the transform MRML node
  vtkSetStringMacro(TransformNodeID);
  vtkGetStringMacro(TransformNodeID);

  // Description:
  // Associated storage MRML node
  vtkMRMLStorageNode* GetStorageNode();

  // Description:
  // Associated display MRML node
  vtkMRMLVolumeDisplayNode* GetDisplayNode();

  // Description:
  // Associated transform MRML node
  vtkMRMLTransformNode* GetTransformNode();

  // Description:
  // Associated ImageData
  vtkGetObjectMacro(ImageData, vtkImageData);
  vtkSetObjectMacro(ImageData, vtkImageData);

  
protected:
  vtkMRMLVolumeNode();
  ~vtkMRMLVolumeNode();
  vtkMRMLVolumeNode(const vtkMRMLVolumeNode&);
  void operator=(const vtkMRMLVolumeNode&);

  // these are unit length direction cosines
  double IJKToRASDirections[3][3];

  // these are mappings to mm space
  double Spacing[3];
  double Origin[3];

  char *StorageNodeID;
  char *DisplayNodeID;
  char *TransformNodeID;

  vtkImageData               *ImageData;

};

#endif


 

