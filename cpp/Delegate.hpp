#pragma once

#include <vector>

/// @brief �P��̃����o�֐����Ǘ�����f���Q�[�^

template<class> class Delegator;  // �O���錾

/// @brief �P��̃����o�֐����Ǘ�����f���Q�[�^
template<class R, class... Args>
class Delegator<R(Args...)>
{

	static Delegator* p;

public:

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<std::is_same<T, void>::value, R>::type
	{
		if (p)
		{
			p->callback(std::forward<Args>(args)...);
		}
	}

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<!std::is_same<T, void>::value, R>::type
	{
		if (p)
		{
			return p->callback(std::forward<Args>(args)...);
		}
		else
		{
			return {};
		}
	}

protected:

	Delegator()
	{
		p = this;
	}

	virtual R callback(Args...) = 0;

};

template<class R, class... Args>
Delegator<R(Args...)>* Delegator<R(Args...)>::p = nullptr;




/// @brief �����̃����o�֐����Ǘ�����f���Q�[�^
template<class> class MultipleDelegator;  // �O���錾

/// @brief �����̃����o�֐����Ǘ�����f���Q�[�^
/// @tparam R �ÓI�֐��̖߂�l
/// @tparam ...Args �ÓI�֐��̈���
template<class R, class... Args>
class MultipleDelegator<R(Args...)>
{

	static std::vector<MultipleDelegator*> pList;

public:

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<std::is_same<T, void>::value, R>::type
	{
		if (pList.empty())
		{
			return;
		}
		for (auto&& it : pList)
		{
			it->callback(std::forward<Args>(args)...);
		}
	}

	template<class T = R>
	static auto Execute(Args... args) -> typename std::enable_if<!std::is_same<T, void>::value, R>::type
	{
		if (pList.empty())
		{
			return {};
		}
		R retval;
		for (auto&& it : pList)
		{
			retval = it->callback(std::forward<Args>(args)...);
		}
		return retval;
	}

protected:

	MultipleDelegator()
	{
		pList.push_back(this);
	}

	virtual R callback(Args...) = 0;

};

template<class R, class... Args>
std::vector<MultipleDelegator<R(Args...)>*> MultipleDelegator<R(Args...)>::pList;

