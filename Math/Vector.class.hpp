/*******************************************************************************
 * fdaudre-@student.42.fr
 *
 *
 ******************************************************************************/

#ifndef		__FDV__VECTOR_CLASS__
# define	__FDV__VECTOR_CLASS__

# include "Core/macro.hpp"

# include <array>

# include <cstring>

FDV_BEGIN_NAMESPACE

template<typename TYPE, std::size_t N_SIZE>
struct VectorImpl
{
		std::array<TYPE, N_SIZE>	data;
};

template<typename TYPE>
struct VectorImpl<TYPE, 2u>
{
		union
		{
			std::array<TYPE, 2u>	data;

			struct
			{
					TYPE			x,
									y;
			};
		};

		VectorImpl(void) = default;

		VectorImpl(TYPE x, TYPE y) :
			data{x, y}
		{
		}
};

template<typename TYPE>
struct VectorImpl<TYPE, 3u>
{
		union
		{
			std::array<TYPE, 3u>	data;

			struct
			{
					TYPE			x,
									y,
									z;
			};
		};

		VectorImpl(void) = default;

		VectorImpl(TYPE x, TYPE y, TYPE z) :
			data{x, y, z}
		{
		}
};

template<typename TYPE>
struct VectorImpl<TYPE, 4u>
{
		union
		{
			std::array<TYPE, 4u>	data;

			struct
			{
					TYPE			x,
									y,
									z,
									w;
			};
		};

		VectorImpl(void) = default;

		VectorImpl(TYPE x, TYPE y, TYPE z, TYPE w) :
			data{x, y, z, w}
		{
		}
};

template<typename TYPE, std::size_t N_SIZE>
class Vector : public VectorImpl<TYPE, N_SIZE>
{
//		inline void
//		_apply(TYPE f(TYPE))
//		{
//			for (TYPE & value : Impl::data)
//			{
//				value = f(value);
//			}
//		}

	public:
		using Impl = VectorImpl<TYPE, N_SIZE>;

		typedef TYPE		*Iterator;
		typedef TYPE const	*ConstIterator;

		typedef void		ApplyFunc(TYPE &);

		Vector(void) = default;

		Vector(TYPE default_value)
		{
			for (TYPE & value : Impl::data)
			{
				value = default_value;
			}
		}


		inline TYPE &
		operator[](std::size_t index)
		{
			return Impl::data[index];
		}

		inline TYPE
		operator[](std::size_t index) const
		{
			return Impl::data[index];
		}


		inline bool
		operator==(Vector & other)
		{
			return not std::memcmp(	static_cast<void *>(&(other.Impl::data[0])),
									static_cast<void *>(&(Impl::data[0])),
									sizeof Impl::data);
		}

		inline bool
		operator!=(Vector & other)
		{
			return not this->operator==(other);
		}


		Vector
		operator+(Vector & other)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] + other.Impl::data[i];
			}
			return ans;
		}

		Vector
		operator+(TYPE value)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] + value;
			}
			return ans;
		}

		Vector &
		operator+=(Vector & other)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] += other.Impl::data[i];
			}
			return *this;
		}

		Vector &
		operator+=(TYPE value)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] += value;
			}
			return *this;
		}

		Vector
		operator-(Vector & other)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] - other.Impl::data[i];
			}
			return ans;
		}

		Vector
		operator-(TYPE value)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] - value;
			}
			return ans;
		}

		Vector &
		operator-=(Vector & other)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] -= other.Impl::data[i];
			}
			return *this;
		}

		Vector &
		operator-=(TYPE value)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] -= value;
			}
			return *this;
		}

		Vector
		operator*(Vector & other)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] * other.Impl::data[i];
			}
			return ans;
		}

		Vector
		operator*(TYPE value)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] * value;
			}
			return ans;
		}

		Vector &
		operator*=(Vector & other)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] *= other.Impl::data[i];
			}
			return *this;
		}

		Vector &
		operator*=(TYPE value)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] *= value;
			}
			return *this;
		}

		Vector
		operator/(Vector & other)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] / other.Impl::data[i];
			}
			return ans;
		}

		Vector
		operator/(TYPE value)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] / value;
			}
			return ans;
		}

		Vector &
		operator/=(Vector & other)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] /= other.Impl::data[i];
			}
			return *this;
		}

		Vector &
		operator/=(TYPE value)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] /= value;
			}
			return *this;
		}

		Vector
		operator%(Vector & other)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] % other.Impl::data[i];
			}
			return ans;
		}

		Vector
		operator%(TYPE value)
		{
			Vector	ans;

			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				ans[i] = Impl::data[i] % value;
			}
			return ans;
		}

		Vector &
		operator%=(Vector & other)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] %= other.Impl::data[i];
			}
			return *this;
		}

		Vector &
		operator%=(TYPE value)
		{
			for (std::size_t i(0) ; i < N_SIZE ; ++i)
			{
				Impl::data[i] %= value;
			}
			return *this;
		}


		Iterator
		begin(void)
		{
			return &(Impl::data[0]);
		}
		Iterator
		end(void)
		{
			return &(Impl::data[N_SIZE]);
		}

		ConstIterator
		begin(void) const
		{
			return &(Impl::data[0]);
		}
		ConstIterator
		end(void) const
		{
			return &(Impl::data[N_SIZE]);
		}

		ConstIterator
		cbegin(void) const
		{
			return &(Impl::data[0]);
		}
		ConstIterator
		cend(void) const
		{
			return &(Impl::data[N_SIZE]);
		}
};

// here bool logic operators

template<typename TYPE>
using Vector2 = Vector<TYPE, 2u>;

template<typename TYPE>
using Vector3 = Vector<TYPE, 3u>;

template<typename TYPE>
using Vector4 = Vector<TYPE, 4u>;

FDV_END_NAMESPACE

#endif // __FDV__VECTOR_CLASS__
