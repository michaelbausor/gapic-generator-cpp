#include <cstdlib>
#include <iostream>

#include "google/cloud/vision/v1/image_annotator.pb.h"
#include "google/cloud/vision/v1/image_annotator.gapic.h"
#include "google/cloud/vision/v1/image_annotator_stub.gapic.h"


int main () {

  std::string image_url = "https://cloud.google.com/_static/d179425f4c/images/cloud/cloud-logo.svg";

  ImageAnnotator client(CreateImageAnnotatorStub());

  ::google::cloud::vision::v1::BatchAnnotateImagesRequest request;
  ::google::cloud::vision::v1::AnnotateImageRequest* annotate_request = request.add_requests();
  annotate_request->mutable_image()->mutable_source()->set_image_uri(image_url);
  ::google::cloud::vision::v1::Feature* feature = annotate_request->add_features();
  feature->set_type(::google::cloud::vision::v1::Feature_Type::Feature_Type_LOGO_DETECTION);

  auto response = client.BatchAnnotateImages(request);

  if (!response) {
    std::cerr << "Request failed!\n";
    std::cerr << response.status().code() << "\n";
    std::cerr << response.status().message() << "\n";
    std::exit(1);
  }

  for (int i = 0; i < response->responses_size(); i++) {
    std::cout << "Response (" << i << "):\n";
    for (int j = 0; j < response->responses(i).logo_annotations_size(); j++) {
      auto entity = response->responses(i).logo_annotations(j);
      std::cout << "  Logo (" << j << "): " << entity.description() << "\n";
    }
  }
}
