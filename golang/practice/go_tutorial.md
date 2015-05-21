Go����ѧϰ�ʼ�
========================
####����֪ʶ
1. Golang��һ��ʹ�ó���Ա������Ч�ʵĿ�Դ��Ŀ��Go����**���������ࡢ��������Ч��**�ġ�
���Ĳ��л���ʹ������ױ�д��˺�����Ӧ�á��������**����ϵͳ**�������е��Ե�ģ�黯����
Go���뵽������ǳ����٣�ͬʱ���б������������պ�ǿ�������ʱ���䡣Golang�ǿ��ٵľ�̬���ͱ������ԣ�
���Ǹо����Ƕ�̬���͵ģ����������ԡ�
Go��һЩ����ʹ��Golang���ڲ�ͬ��
    1. ���������
    2. ����
    3. Channel
    4. ���� 
    5. ��ȫ
    6. ��׼��ʽ��
    7. ���ͺ���
    8. UTF-8, �κεط�����UTF-8�ģ������ַ����Լ�������롣
    9. ��Դ
    10. ����
���е�Go�ļ���package <something>��ͷ�����ڶ������е�ִ���ļ�������package main
2. ������ ���ͣ� �ؼ���
        var a int
        var b bool
        a = 15
        b = false
        a := 15
����var�������Գ���
        var (
        x int
        b bool
        )
Ҳ����ƽ�и�ֵ
        a, b := 34, 45
        a, b := 1, "hello world"
Golang�������δʹ�õı�������
    1. ��������, true, false
    2. ��������, int����Ӳ�������ʵ��ĳ��ȡ����ϣ����ȷ�䳤�ȣ�����ʹ��int32����uint32��
byte��uint8�ı�����
    3. ����
            const (
                a = iota
                b = iota
            )
��iota�ٴ����µ�һ��ʹ��ʱ������ֵ������1��iotaҲ����ʡ��ʹ�á�
iotaֵΪ�䶨�����ڵ���������ʼλ��Ϊ0.

    4. �ַ����� �ڽ�������string, һ����������ֵ���ַ����Ͳ����޸��ˡ���Go���ַ����ǲ��ɱ�ġ�
            s := "hello"
            c := []rune(s)
            c[0] = 'c'
            s2 := string(c)
        ���ڶ����ַ�����д��������ʾ:
            s := "starting part" + 
                "end part"
        rune��int32�ı�������UTF-8���б��롣һ���ڵ���Ҫ�����ַ����е��ַ�ʱʹ�á�����
        ѭ��ÿ���ֽڡ�
    5. ����Ϊ�˴�������ڵ��ڽ����͡���error��error������һ���ӿڡ�

3. ���ƽṹ

    ��Golang����û��do whileѭ����ֻ��for����switch����if��select������Բ���ţ�
�������������ǰ����ڴ������ڡ�
    Golang�е�forѭ����������ʽ��
        for init; condition; post {}
        for condition {}
        for {}
    ��for��ִ�ж��������Ӧ��ʹ��ƽ�и�ֵ����Ҫ����Goû�ж��ű��ʽ��

    range��������ѭ���� ������slice, array, string, map��channel��ʹ�á�range��һ����������
    ��������ʱ������ѭ���������з���һ����ֵ�ԡ�
    ����slice����array��ѭ��ʱ��range�������Ϊ���������Ŷ�Ӧ��������Ϊֵ��
    
    switch�÷�����
4. �ڽ�����

    1. close, ����channelͨѶ���������ر�channel��
    2. delete, ������map��ɾ��ʵ����
    3. len��cap, len���ڷ����ַ�����slice������ĳ��ȡ�
    4. new���ڸ������͵��ڴ���䡣
    5. make�����ڽ�����(map, slice��channel)���ڴ���䡣
    6. copy���ڸ���slice
    7. append����׷��slice
    8. panic��recover, �����쳣������ơ�
    9. print��println, �����ڲ�����fmt���������ʹ�ã���Ҫ���ڵ��ԡ�
    10. complex, real��imag�� ȫ�����ڴ����ơ�
5. array, slice��map��ʹ��
    array ��[n]<type>���壬n��ʾarray�ĳ��ȣ�<type>��ʾϣ���洢�����ݵ����͡�
    slice��array�ӽ����������µ�Ԫ�ؼ����ʱ��������ӳ��ȡ�slice����ָ��ײ��һ��array��
    slice���������ͣ���һ��ָ��array��ָ�롣��slice���޸Ļᷴӳ���ײ��array�ϡ�
    �����Ҫ�ڸ����Ͻ����޸ģ����Զ�ԭ�е�slice���п�����
        list := []string {"a", "b", "c"}
        for k, v := range list {
                log.Println(k, "-", v)
        }
        slice := make([]string, len(list) - 1)
        copy(slice, list[1:])
        slice[1] = "d"
        for k, v := range list {
                log.Println(k, "-", v)
        }
    ͬ��ʹ��append������չslice����չ���append���ڸ����Ͻ���append��
        s2 := append(list, "e")
        s2[2] = "ggg"
        for k, v := range s2 {
                log.Println(k, "-", v)
        }
        for k, v := range list {
                log.Println(k, "-", v)
        }
map���� map[<from_type>]<to_type>
    1. ��map���Ԫ�أ�m["k"] = 1
    2. ���Ԫ���Ƿ���ڣ� value, present = m["k"]
    3. ɾ��Ԫ�� delete(m, "k")
)
