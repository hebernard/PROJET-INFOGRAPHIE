#include "filtering.h"

ofTexture applyFilter(ofTexture& texture, filterType type)
{
    if (!texture.isAllocated())
    {
        std::cout << "No filter applied" << std::endl;
        return ofTexture();
    }

    ofPixels pixels;
    ofPixels output;
    texture.readToPixels(pixels);
    texture.readToPixels(output);

    int width = pixels.getWidth();
    int height = pixels.getHeight();


    float sum[color_component_count];

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int c = 0; c < color_component_count; ++c)
                sum[c] = 0;

            int indexOut = (width * y + x) * color_component_count;

            for (int j = -kernel_offset; j <= kernel_offset; ++j)
            {
                for (int i = -kernel_offset; i <= kernel_offset; ++i)
                {
                    // calculer les indices d'échantillonnage
                    int xi = x - i;
                    int yj = y - j;

                    // traitement de la bordure
                    if (xi < 0 || xi > width || yj < 0 || yj > height)
                        continue;

                    // déterminer l'index du pixel de l'image source à lire
                    int indexIn = (width * yj + xi) * color_component_count;

                    // lire la couleur du pixel de l'image source
                    ofColor colorIn = pixels.getColor(indexIn);

                    // déterminer l'indice du facteur à lire dans le kernel de convolution
                    int kernelIndex = kernel_size * (j + kernel_offset) + (i + kernel_offset);

                    int kernelValue;
                    switch (type)
                    {
                    case filterType::Identity:
                        kernelValue = convolution_kernel_identity.at(kernelIndex);
                        break;
                    case filterType::Emboss:
                        kernelValue = convolution_kernel_emboss.at(kernelIndex);
                        break;
                    case filterType::Blur:
                        kernelValue = convolution_kernel_blur.at(kernelIndex);
                        break;
                    case filterType::Sharpen:
                        kernelValue = convolution_kernel_sharpen.at(kernelIndex);
                        break;
                    case filterType::EdgeDetect:
                        kernelValue = convolution_kernel_edge_detect.at(kernelIndex);
                        break;
                    default:
                        kernelValue = convolution_kernel_identity.at(kernelIndex);
                        break;
                    }

                    // itération sur les composantes de couleur
                    for (int c = 0; c < color_component_count; ++c)
                    {
                        // accumuler les valeurs de filtrage en fonction du kernel de convolution
                        sum[c] = sum[c] + kernelValue * colorIn[c];
                    }
                }
            }

            ofColor colorOut;

            // déterminer la couleur du pixel à partir des valeurs de filtrage accumulées pour chaque composante
            for (int c = 0; c < color_component_count; ++c)
            {
                // conversion vers entier et validation des bornes de l'espace de couleur
                colorOut[c] = (int)ofClamp(sum[c], 0, 255);
            }

            // écrire la couleur à l'index du pixel en cours de filtrage
            output.setColor(indexOut, colorOut);
        }
    }

    ofTexture tex;
    tex.loadData(output);

    return tex;

    //std::cout << "Applied filter: " << getFilterTypes()[] << std::endl;
}

std::vector<string> getFilterTypes()
{
    return { "Identity", "Emboss", "Blur", "Sharpen", "Edge detect" };
}
