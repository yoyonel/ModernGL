'''
    ModernGL Program members
'''

# from ModernGL import ModernGL as _mgl

class Uniform:
    '''
        Uniform
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Uniform')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Uniform.__new__(Uniform)
        res.mglo = obj
        return res

    @property
    def name(self) -> str:
        '''
            name
        '''

        return self.mglo.name

    @property
    def location(self) -> int:
        '''
            location
        '''

        return self.mglo.location

    @property
    def dimension(self) -> int:
        '''
            dimension
        '''

        return self.mglo.dimension

    @property
    def array_length(self) -> int:
        '''
            array_length
        '''

        return self.mglo.array_length

    @property
    def value(self):
        '''
            value
        '''

        return self.mglo.value

    @value.setter
    def value(self, value):
        self.mglo.value = value


class UniformBlock:
    '''
        UniformBlock
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('UniformBlock')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = UniformBlock.__new__(UniformBlock)
        res.mglo = obj
        return res

    @property
    def name(self):
        '''
            name
        '''

        return self.mglo.name

    @property
    def location(self):
        '''
            location
        '''

        return self.mglo.location


class Varying:
    '''
        Varying
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Varying')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Varying.__new__(Varying)
        res.mglo = obj
        return res

    @property
    def name(self):
        '''
            name
        '''

        return self.mglo.name

    @property
    def number(self):
        '''
            number
        '''

        return self.mglo.number


class UniformMap:
    '''
        UniformMap
    '''

    def __init__(self):
        self.mglo = {}
        raise NotImplementedError('UniformMap')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = UniformMap.__new__(UniformMap)
        res.mglo = obj
        return res

    def __getitem__(self, key) -> Uniform:
        '''
        '''

        return Uniform.new(self.mglo[key])

    def __contains__(self, key):
        return key in self.mglo

    def __len__(self):
        return len(self.mglo)


class Attribute:
    '''
        Attribute
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Attribute')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Attribute.__new__(Attribute)
        res.mglo = obj
        return res

    @property
    def name(self):
        '''
            name
        '''

        return self.mglo.name

    @property
    def location(self):
        '''
            location
        '''

        return self.mglo.location

    @property
    def array_length(self):
        '''
            array_length
        '''

        return self.mglo.array_length

    @property
    def dimension(self):
        '''
            dimension
        '''

        return self.mglo.dimension

    @property
    def shape(self):
        '''
            shape
        '''

        return self.mglo.shape


class AttributeMap:
    '''
        AttributeMap
    '''

    def __init__(self):
        self.mglo = {}
        raise NotImplementedError('AttributeMap')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = UniformMap.__new__(UniformMap)
        res.mglo = obj
        return res

    def __getitem__(self, key) -> Attribute:
        '''
        '''

        return Attribute.new(self.mglo[key])

    def __contains__(self, key):
        return key in self.mglo

    def __len__(self):
        return len(self.mglo)
