#include "pch.h"
#include "AboutPage.h"
#if __has_include("AboutPage.g.cpp")
#include "AboutPage.g.cpp"
#endif
#include "Win32Utils.h"

namespace winrt::Magpie::App::implementation {

void AboutPage::BugReportButton_Click(IInspectable const&, RoutedEventArgs const&) {
	Win32Utils::ShellOpen(L"https://github.com/Blinue/Magpie/issues/new?assignees=&labels=bug&template=01_bug.yaml");
}

void AboutPage::FeatureRequestButton_Click(IInspectable const&, RoutedEventArgs const&) {
	Win32Utils::ShellOpen(L"https://github.com/Blinue/Magpie/issues/new?assignees=&labels=enhancement&template=03_request.yaml");
}

void AboutPage::DiscussionsButton_Click(IInspectable const&, RoutedEventArgs const&) {
	Win32Utils::ShellOpen(L"https://github.com/Blinue/Magpie/discussions");
}

}
