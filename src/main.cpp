#define _SCL_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#define TINYOBJLOADER_IMPLEMENTATION

#include "RenderThread.h"
#include <vector>
#include <thread>

void CalcIntersections()
{
	std::shared_ptr<bitmap_image> image = std::make_shared<bitmap_image>(WIDTH, HEIGHT);
	auto nThreads = std::thread::hardware_concurrency();

	std::cout << "Resolution: " << WIDTH << "x" << HEIGHT << std::endl;
	std::cout << "Supersampling: " << SUPERSAMPLING << std::endl;
	std::cout << "Ray depth: " << DEPTH << std::endl;
	std::cout << "Threads: " << nThreads << std::endl;

	std::vector<RenderThread> renderThreads(nThreads);
	std::vector<std::thread> tt;

	auto size = WIDTH*HEIGHT;

	auto chunk = size / nThreads;
	auto rem = size % nThreads;

	//launch threads
	for (unsigned i = 0; i < nThreads - 1; i++)
	{
		tt.emplace_back(std::thread(&RenderThread::LaunchThread, &renderThreads[i], i * chunk, (i + 1) * chunk, image));
	}
	tt.emplace_back(std::thread(&RenderThread::LaunchThread, &renderThreads[nThreads-1], (nThreads - 1)*chunk, nThreads*chunk + rem, image));

	for (auto& t : tt)
		t.join();

	auto saveString = std::to_string(int(WIDTH)) + "x" + std::to_string(int(HEIGHT)) + ", " + std::to_string(SUPERSAMPLING) + "x SS.bmp";
	image->save_image(saveString);
	std::cout << "Output filename: " << saveString << std::endl;
}

int main()
{
	auto timeStart = std::chrono::high_resolution_clock::now();
	CalcIntersections();

	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto passedTime = std::chrono::duration<FPType, std::milli>(timeEnd - timeStart).count();
	//std::cout << std::endl << "Triangles: " << triangleCount / std::thread::hardware_concurrency() << std::endl;
	//std::cout << "BBox tests: " << bboxTests << std::endl;
	//std::cout << "BBox intersections: " << bboxIntersections << std::endl;
	//std::cout << "Triangle tests: " << triangleTests << std::endl;
	//std::cout << "Triangle intersections: " << triangleIntersections << std::endl;
	//printf("Total number of primary rays                    : %i\n", int(numPrimaryRays));
	//printf("Total number of primary rays that intersected   : %i\n", int(numPrimaryHitRays));
	//printf("Total number of secondary rays                  : %i\n", int(numSecondaryRays));
	//printf("Total number of secondary rays that intersected : %i\n", int(numSecondaryHitRays));
	std::cout << "Time: " << passedTime / 1000 << " seconds" << std::endl;
	
	std::cout << "\nPress enter to exit...";
	std::cin.ignore();

	return 0;
}