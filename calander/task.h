#pragma once

#include <QString>
#include <QDateTime>
#include <QTime>

// 优先级枚举
   enum  Priority {
       Low,      // 低
       Medium,   // 中
       High      // 高
   };

   // 状态枚举
   enum Status {
       Pending,  // 未完成
       InProgress,  // 进行中
       Completed  // 已完成
   };

// 任务结构体
    struct Task {
        int task_id;             // 任务ID
        QString title;           // 任务标题
        Priority priority;       // 优先级（low、medium、high）
        Status status;           // 状态（未完成、进行中、已完成）
        QDateTime create_time;   // 创建时间
        QDateTime due_time;      // 截止时间
        QTime duration;          // 持续时间

        // 构造函数
        Task(int id, const QString &taskTitle, Priority taskPriority, Status taskStatus,
             const QDateTime &createTime, const QDateTime &dueTime, const QTime &taskDuration)
            : task_id(id), title(taskTitle), priority(taskPriority), status(taskStatus),
            create_time(createTime), due_time(dueTime), duration(taskDuration) {}
    };
