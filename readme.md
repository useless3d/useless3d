Documentation will get better as things become more concrete. Right now the basic structure is:

```
> App (singleton responsible for managing window, input, and kicking off the main loop)
	> Scene (collection of stages)
		> Stages
			> Camera (base class for PerspectiveCamera and OrthographicCamera)
			> Meshes (Stage owns unique instances of meshes and hands out pointers, ie 10 props could share the same mesh)
			> Props (are transformable)
				> Mesh (pointer to mesh managed by stage)
					> Renderable (tracks gpu state and draws mesh) (optional as not required if headless)
			> Actors (are transformable and animatable) (not currently implemented)
```