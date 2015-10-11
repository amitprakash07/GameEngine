#include "GameObject.h"

Engine::GameObject::GameObject(SharedPointer<Engine::Graphics::Mesh> i_mesh, SharedPointer<Engine::Graphics::Effect> i_effect)
{
	if (!i_mesh.isNull())
		mMesh = i_mesh;
	if (!i_effect.isNull())
		mEffect = i_effect;
	renderable = true;
	mPositionOffset.x = 0.0f;
	mPositionOffset.y = 0.0f;
	mPositionOffset.z = 0.0f;
}
Engine::SharedPointer<Engine::Graphics::Mesh> Engine::GameObject::getMesh()
{
	return mMesh;
}
Engine::SharedPointer<Engine::Graphics::Effect> Engine::GameObject::getEffect()
{
	return mEffect;
}
bool Engine::GameObject::isRenderable()
{
	return renderable;
}
void Engine::GameObject::HandleMessage(Engine::utils::StringHash &, void *i_MessageSender, void* i_pMessageData)
{
	
}




