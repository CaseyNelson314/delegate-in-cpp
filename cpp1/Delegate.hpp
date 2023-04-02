#pragma	onve

template<class, class> class Delegator;  // �O���錾

/// @brief �P��̃����o�֐����Ǘ�����f���Q�[�^
template<class T, class R, class... Args>
class Delegator<T, R(Args...)>
{

	using Functor = R(T::*)(Args...);

	static T* object;
	static Functor functionPtr;

public:

	Delegator(T* obj, Functor callback)
	{
		object = obj;
		functionPtr = callback;
	}

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<std::is_same<T, void>::value, R>::type
	{
		if (object)
		{
			(object->*functionPtr)(std::forward<Args>(args)...);
		}
	}

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<!std::is_same<T, void>::value, R>::type
	{
		if (object)
		{
			return (object->*functionPtr)(std::forward<Args>(args)...);
		}
		else
		{
			return {};
		}
	}
};

template<class T, class R, class... Args>
T* Delegator<T, R(Args...)>::object = nullptr;

template<class T, class R, class... Args>
typename Delegator<T, R(Args...)>::Functor Delegator<T, R(Args...)>::functionPtr;


#include <vector>

/// @brief �����̃����o�֐����Ǘ�����f���Q�[�^
template<class, class> class MultipleDelegator;  // �O���錾

/// @brief �����̃����o�֐����Ǘ�����f���Q�[�^
/// @tparam R �ÓI�֐��̖߂�l
/// @tparam ...Args �ÓI�֐��̈���
template<class T, class R, class... Args>
class MultipleDelegator<T, R(Args...)>
{

	using Functor = R(T::*)(Args...);

	struct MemberFuction
	{
		T* object;
		Functor functionPtr;
	};

	static std::vector<MemberFuction> functions;

public:

	MultipleDelegator(T* obj, Functor callback)
	{
		functions.push_back({ obj, callback });
	}

	void add(T* obj, Functor callback)
	{
		functions.push_back({ obj, callback });
	}

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<std::is_same<T, void>::value, R>::type
	{
		if (functions.empty())
		{
			return;
		}
		for (auto&& it : functions)
		{
			(it.object->*it.functionPtr)(args...);
		}
	}

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<!std::is_same<T, void>::value, R>::type
	{
		if (functions.empty())
		{
			return {};
		}
		R retval;
		for (auto&& it : functions)
		{
			retval = (it.object->*it.functionPtr)(args...);
		}
		return retval;
	}

};

template<class T, class R, class... Args>
std::vector<typename MultipleDelegator<T, R(Args...)>::MemberFuction> MultipleDelegator<T, R(Args...)>::functions;

