#pragma once

namespace Floppa {

	template <typename T>
	class SmartPointer {
	public:
		SmartPointer() : m_p(nullptr) {}
		SmartPointer(T* p) : m_p(p) {}
		
		SmartPointer(SmartPointer const&) = delete;
		SmartPointer& operator=(SmartPointer const&) = delete;

		SmartPointer(SmartPointer&& o) : m_p(o.release()) {}

		SmartPointer& operator=(SmartPointer&& o) {
			this->~SmartPointer();
			m_p = o.release();
			return *this;
		}

		~SmartPointer() {
			if (m_p)
				delete m_p;
		}

	public:
		T* release(T* new_p = nullptr) {
			T* prev_p = m_p;
			m_p = new_p;
			return prev_p;
		}

		T* get() {
			return m_p;
		}

		T* operator->() {
			return m_p;
		}

		T& operator*() {
			return *m_p;
		}

		operator T* () {
			return m_p;
		}

		operator bool() {
			return m_p != nullptr;
		}

		SmartPointer& operator=(T* p) {
			this->~SmartPointer();
			m_p = p;
			return *this;
		}
		
	private:
		T* m_p;
	};

	template <typename T>
	void deallocate(SmartPointer<T>& sp) {
		delete sp.release();
	}

}