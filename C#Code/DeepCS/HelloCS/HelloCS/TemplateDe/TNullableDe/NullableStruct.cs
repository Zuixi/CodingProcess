using System;
using System.Collections.Generic;
using System.Linq;

namespace HelloCS.TemplateDe.TNullableDe
{
    // define some nullable struct and else define a constrains
    public struct Nullable<T>
        where T : struct
    {
        private bool hashValue;
        public bool HasValue
        {
            get { return this.hashValue; }
        }
        public Nullable(T value)
        {
            this.hashValue = true;
            this.value = value;
        }

        private T value;
        public T Value
        {
            get
            {
                if (!hashValue)
                {
                    throw new InvalidOperationException();
                }
                return value;
            }
        }

        public static explicit operator T(Nullable<T> value)
        {
            return value.Value;
        }

        public static implicit operator Nullable<T>(T value)
        {
            return new Nullable<T>(value);
        }

        public override string ToString()
        {
            if (!hashValue)
            {
                return String.Empty;
            }
            return this.value.ToString();

        }

    }

}
