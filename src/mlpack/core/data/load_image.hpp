/**
 * @file load_image.hpp
 * @author Mehul Kumar Nirala
 *
 * An image loading utillity
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */

#ifndef MLPACK_CORE_DATA_LOAD_IMAGE_HPP
#define MLPACK_CORE_DATA_LOAD_IMAGE_HPP

#include <mlpack/core.hpp>
#include <mlpack/core/util/log.hpp>
#include <mlpack/prereqs.hpp>

#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
    && __has_include(<filesystem>)
#include <filesystem>
#define HAS_FILESYSTEM 1
namespace fs = std::filesystem;
#endif

#include "extension.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace mlpack {
namespace data {

/**
 * Loads a matrix with image. It also supports loading image from 
 * an entire directory.
 * @code
 * arma::Mat<unsigned char> img;
 * data::LoadImage loader;
 * loader.Load("test_image.png", std::move(img));
 * @endcode
 *
 * The supported types of files are:
 * 
 * - JPEG baseline & progressive (12 bpc/arithmetic not supported,
 *    same as stock IJG lib)
 * - PNG 1/2/4/8/16-bit-per-channel
 * - TGA (not sure what subset, if a subset)
 * - BMP non-1bpp, non-RLE
 * - PSD (composited view only, no extra channels, 8/16 bit-per-channel)
 * - GIF (*comp always reports as 4-channel)
 * - HDR (radiance rgbE format)
 * - PIC (Softimage PIC)
 * - PNM (PPM and PGM binary only).
 */
class LoadImage
{
 public:
  /**
   * LoadImage default constructor.
   */
  LoadImage();

  /**
   * Instantiate the LoadImage object with the image width, height, channels.
   *
   * @param width Matrix width for the output matrix.
   * @param height Matrix height for the output matrix.
   * @param channels Matrix channels for the output matrix.
   */
  LoadImage(size_t width, size_t height, size_t channels);

  /**
   * Checks if the given image filename is supported.
   *
   * @param filename Name of the image file.
   * @return Boolean value indicating success if it is an image.
   */
  bool ImageFormatSupported(const std::string& fileName);

  /**
   * Load the image file into the given matrix.
   *
   * @param fileName Name of the image file.
   * @param flipVertical Flip the image vertical upon loading.
   * @param outputMatrix Matrix to load into.
   * @return Boolean value indicating success or failure of load.
   */
  bool Load(const std::string& fileName,
            bool flipVertical,
            arma::Mat<unsigned char>&& outputMatrix);

  /**
   * Load the image file into the given matrix.
   *
   * @param fileName Name of the image file.
   * @param flipVertical Flip the image vertical upon loading.
   * @param width Width of the image file.
   * @param height Height of the image file.
   * @param channels Channels of the image file.
   * @param outputMatrix Matrix to load into.
   * @return Boolean value indicating success or failure of load.
   */
  bool Load(const std::string& fileName,
            bool flipVertical,
            arma::Mat<unsigned char>&& outputMatrix,
            size_t *width,
            size_t *height,
            size_t *channels);

  /**
   * Load the image file into the given matrix.
   *
   * @param files A vector containing names of the image file to be loaded.
   * @param flipVertical Flip the image vertical upon loading.
   * @param outputMatrix Matrix to load into.
   * @return Boolean value indicating success or failure of load.
   */
  bool Load(const std::vector<std::string>& files,
            bool flipVertical,
            arma::Mat<unsigned char>&& outputMatrix);

  /**
   * Load the image file into the given matrix.
   *
   * @param dirPath Path containing the image files.
   * @param flipVertical Flip the image vertical upon loading.
   * @param outputMatrix Matrix to load into.
   * @return Boolean value indicating success or failure of load.
   */
  bool LoadDIR(const std::string& dirPath,
               bool flipVertical,
               arma::Mat<unsigned char>&& outputMatrix);

  /**
   * LoadImage default destructor.
   */
  ~LoadImage();

 private:
  // To store supported image types.
  std::vector<std::string> fileTypes;

  // To store matrixWidth.
  size_t matrixWidth;

  // To store matrixHeight.
  size_t matrixHeight;

  // To store channels.
  size_t channels;
};

} // namespace data
} // namespace mlpack

// Include implementation of LoadImage.
#include "load_image_impl.hpp"

#endif
