/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkExceptionObject.h"

#include "otbMultiChannelRAndBAndNIRVegetationIndexImageFilter.h"
#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbVegetationIndex.h"

template<class TInputImage, class TOutputImage, class TFunction>
int generic_MultiChannelRAndBAndNIRVegetationIndexImageFilter(int argc, char * argv[])
{
  try
    {

        typedef otb::ImageFileReader<TInputImage> ReaderType;
        typedef otb::ImageFileWriter<TOutputImage> WriterType;

        typedef otb::MultiChannelRAndBAndNIRVegetationIndexImageFilter<TInputImage,TOutputImage,TFunction> 
                                                MultiChannelRAndBAndNIRVegetationIndexImageFilterType;

        // Instantiating object
        typename MultiChannelRAndBAndNIRVegetationIndexImageFilterType::Pointer filter = MultiChannelRAndBAndNIRVegetationIndexImageFilterType::New();
        typename ReaderType::Pointer reader = ReaderType::New();
        typename WriterType::Pointer writer = WriterType::New();

        const char * inputFilename  = argv[1];
        const char * outputFilename = argv[2];
        unsigned int redChannel(::atoi(argv[3]));
        unsigned int blueChannel(::atoi(argv[4]));
        unsigned int nirChannel(::atoi(argv[5]));
        double gamma(::atof(argv[6]));
        reader->SetFileName( inputFilename );
        writer->SetFileName( outputFilename  );
        filter->SetRedIndex(redChannel);
        filter->SetBlueIndex(blueChannel);
        filter->SetNIRIndex(nirChannel);
        filter->GetFunctor().SetGamma(gamma);
        filter->SetInput( reader->GetOutput() ); 
        writer->SetInput( filter->GetOutput() );
        writer->Update();

    }

  catch( itk::ExceptionObject & err ) 
    { 
    std::cout << "Exception itk::ExceptionObject thrown !" << std::endl; 
    std::cout << err << std::endl; 
    return EXIT_FAILURE;
    } 

  catch( ... ) 
    { 
    std::cout << "Unknown exception thrown !" << std::endl; 
    return EXIT_FAILURE;
    } 
  return EXIT_SUCCESS;


}

int otbMultiChannelRAndBAndNIRVegetationIndexImageFilter(int argc, char * argv[])
{
        const unsigned int Dimension = 2;
        typedef otb::VectorImage<unsigned char ,Dimension> InputImageType;
        typedef otb::Image<float,Dimension> OutputImageType;
        
        std::string strArgv(argv[1]);
        argc--;
        argv++;
	if ( strArgv == "ARVI" ) return( generic_MultiChannelRAndBAndNIRVegetationIndexImageFilter<InputImageType, OutputImageType,
                                                otb::Functor::ARVI<     InputImageType::InternalPixelType,
                                                                        InputImageType::InternalPixelType,
                                                                        InputImageType::InternalPixelType,
                                                                        OutputImageType::PixelType> >
                                                                        (argc,argv) );
        else
                return EXIT_FAILURE;
        return EXIT_SUCCESS;
}
