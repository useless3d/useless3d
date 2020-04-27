import bpy

# Define the name of the giant action containing all other sub-actions
base_action_name = "bend"

# Define the name, start, and end frame of each sub animation
sub_actions = [
    ("sub_bend_001", 0, 14)
    ,("sub_bend_002", 15, 29)
]

for a in sub_actions:
	print("processing: " + a[0])
    new_action = bpy.data.actions.get(base_action_name).copy()
    new_action.name = a[0]
    for fc in new_action.fcurves:
        # Remove unwanted frames
        for i in reversed(range(0, len(fc.keyframe_points))):
            kfp = fc.keyframe_points[i]
            frame_number = int(kfp.co[0])
            if frame_number < a[1] or frame_number > a[2]:
                fc.keyframe_points.remove(kfp)
        # Shift remaining frames
        offset = fc.keyframe_points[0].co[0]
        for kfp in fc.keyframe_points:
            kfp.co[0] = kfp.co[0] - offset
            kfp.handle_left[0] = kfp.handle_left[0] - offset
            kfp.handle_right[0] = kfp.handle_right[0] - offset
            