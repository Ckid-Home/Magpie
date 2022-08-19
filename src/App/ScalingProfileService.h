#pragma once
#include "pch.h"
#include "ScalingProfile.h"
#include "WinRTUtils.h"


namespace winrt::Magpie::App {

class ScalingProfileService {
public:
	static ScalingProfileService& Get() {
		static ScalingProfileService instance;
		return instance;
	}

	bool TestNewProfile(bool isPackaged, std::wstring_view pathOrAumid, std::wstring_view className);

	bool AddProfile(bool isPackaged, std::wstring_view pathOrAumid, std::wstring_view className, std::wstring_view name, int copyFrom);

	event_token ProfileAdded(delegate<ScalingProfile&> const& handler) {
		return _profileAddedEvent.add(handler);
	}

	WinRTUtils::EventRevoker ProfileAdded(auto_revoke_t, delegate<ScalingProfile&> const& handler) {
		event_token token = ProfileAdded(handler);
		return WinRTUtils::EventRevoker([this, token]() {
			ProfileAdded(token);
		});
	}

	void ProfileAdded(event_token const& token) {
		_profileAddedEvent.remove(token);
	}

	void RenameProfile(uint32_t profileIdx, std::wstring_view newName);

	event_token ProfileRenamed(delegate<uint32_t> const& handler) {
		return _profileRenamedEvent.add(handler);
	}

	WinRTUtils::EventRevoker ProfileRenamed(auto_revoke_t, delegate<uint32_t> const& handler) {
		event_token token = ProfileRenamed(handler);
		return WinRTUtils::EventRevoker([this, token]() {
			ProfileRenamed(token);
		});
	}

	void ProfileRenamed(event_token const& token) {
		_profileRenamedEvent.remove(token);
	}

	void RemoveProfile(uint32_t profileIdx);

	event_token ProfileRemoved(delegate<uint32_t> const& handler) {
		return _profileRemovedEvent.add(handler);
	}

	WinRTUtils::EventRevoker ProfileRemoved(auto_revoke_t, delegate<uint32_t> const& handler) {
		event_token token = ProfileRemoved(handler);
		return WinRTUtils::EventRevoker([this, token]() {
			ProfileRemoved(token);
		});
	}

	void ProfileRemoved(event_token const& token) {
		_profileRemovedEvent.remove(token);
	}

	bool ReorderProfile(uint32_t profileIdx, bool isMoveUp);

	event_token ProfileReordered(delegate<uint32_t, bool> const& handler) {
		return _profileReorderedEvent.add(handler);
	}

	WinRTUtils::EventRevoker ProfileReordered(auto_revoke_t, delegate<uint32_t, bool> const& handler) {
		event_token token = ProfileReordered(handler);
		return WinRTUtils::EventRevoker([this, token]() {
			ProfileReordered(token);
		});
	}

	void ProfileReordered(event_token const& token) {
		_profileReorderedEvent.remove(token);
	}

	ScalingProfile& GetProfileForWindow(HWND hWnd);

	ScalingProfile& DefaultScalingProfile();

	ScalingProfile& GetProfile(uint32_t idx);

	uint32_t GetProfileCount();

private:
	ScalingProfileService() = default;

	event<delegate<ScalingProfile&>> _profileAddedEvent;
	event<delegate<uint32_t>> _profileRenamedEvent;
	event<delegate<uint32_t>> _profileRemovedEvent;
	event<delegate<uint32_t, bool>> _profileReorderedEvent;
};

}
