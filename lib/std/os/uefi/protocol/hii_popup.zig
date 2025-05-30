const std = @import("std");
const uefi = std.os.uefi;
const Guid = uefi.Guid;
const Status = uefi.Status;
const hii = uefi.hii;
const cc = uefi.cc;
const Error = Status.Error;

/// Display a popup window
pub const HiiPopup = extern struct {
    revision: u64,
    _create_popup: *const fn (*const HiiPopup, PopupStyle, PopupType, hii.Handle, u16, ?*PopupSelection) callconv(cc) Status,

    pub const CreatePopupError = uefi.UnexpectedError || error{
        InvalidParameter,
        OutOfResources,
    };

    /// Displays a popup window.
    pub fn createPopup(
        self: *const HiiPopup,
        style: PopupStyle,
        popup_type: PopupType,
        handle: hii.Handle,
        msg: u16,
    ) CreatePopupError!PopupSelection {
        var res: PopupSelection = undefined;
        switch (self._create_popup(self, style, popup_type, handle, msg, &res)) {
            .success => return res,
            .invalid_parameter => return Error.InvalidParameter,
            .out_of_resources => return Error.OutOfResources,
            else => |status| return uefi.unexpectedStatus(status),
        }
    }

    pub const guid align(8) = Guid{
        .time_low = 0x4311edc0,
        .time_mid = 0x6054,
        .time_high_and_version = 0x46d4,
        .clock_seq_high_and_reserved = 0x9e,
        .clock_seq_low = 0x40,
        .node = [_]u8{ 0x89, 0x3e, 0xa9, 0x52, 0xfc, 0xcc },
    };

    pub const PopupStyle = enum(u32) {
        info,
        warning,
        @"error",
    };

    pub const PopupType = enum(u32) {
        ok,
        cancel,
        yes_no,
        yes_no_cancel,
    };

    pub const PopupSelection = enum(u32) {
        ok,
        cancel,
        yes,
        no,
    };
};
