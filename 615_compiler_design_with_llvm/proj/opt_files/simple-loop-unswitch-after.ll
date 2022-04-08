; ModuleID = 'simple-loop-unswitch-before.ll'
source_filename = "simple-loop-unswitch.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %6 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %6) #3
  store i32 0, i32* %2, align 4, !tbaa !3
  %7 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %7) #3
  %8 = call i32 (i8*, ...) @__isoc99_scanf(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* noundef %3)
  %9 = bitcast i32* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %9) #3
  store i32 0, i32* %4, align 4, !tbaa !3
  %10 = bitcast i32* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %10) #3
  store i32 0, i32* %5, align 4, !tbaa !3
  %11 = load i32, i32* %3, align 4
  %12 = icmp eq i32 %11, 10
  %.promoted = load i32, i32* %2, align 4, !tbaa !3
  %.promoted1 = load i32, i32* %5, align 4, !tbaa !3
  %.promoted3 = load i32, i32* %4, align 4, !tbaa !3
  br label %13

13:                                               ; preds = %23, %0
  %14 = phi i32 [ %24, %23 ], [ %.promoted3, %0 ]
  %15 = phi i32 [ %25, %23 ], [ %.promoted1, %0 ]
  %16 = phi i32 [ %26, %23 ], [ %.promoted, %0 ]
  %17 = icmp slt i32 %16, 10
  br i1 %17, label %18, label %27

18:                                               ; preds = %13
  br i1 %12, label %19, label %21

19:                                               ; preds = %18
  %20 = add nsw i32 %14, 1
  br label %23

21:                                               ; preds = %18
  %22 = add nsw i32 %15, 1
  br label %23

23:                                               ; preds = %21, %19
  %24 = phi i32 [ %14, %21 ], [ %20, %19 ]
  %25 = phi i32 [ %22, %21 ], [ %15, %19 ]
  %26 = add nsw i32 %16, 1
  br label %13, !llvm.loop !7

27:                                               ; preds = %13
  %.lcssa4 = phi i32 [ %14, %13 ]
  %.lcssa2 = phi i32 [ %15, %13 ]
  %.lcssa = phi i32 [ %16, %13 ]
  store i32 %.lcssa, i32* %2, align 4, !tbaa !3
  store i32 %.lcssa2, i32* %5, align 4, !tbaa !3
  store i32 %.lcssa4, i32* %4, align 4, !tbaa !3
  %28 = load i32, i32* %4, align 4, !tbaa !3
  %29 = bitcast i32* %5 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %29) #3
  %30 = bitcast i32* %4 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %30) #3
  %31 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %31) #3
  %32 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %32) #3
  ret i32 %28
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

declare dso_local i32 @__isoc99_scanf(i8* noundef, ...) #2

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{!"clang version 14.0.0"}
!3 = !{!4, !4, i64 0}
!4 = !{!"int", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C/C++ TBAA"}
!7 = distinct !{!7, !8, !9}
!8 = !{!"llvm.loop.mustprogress"}
!9 = !{!"llvm.loop.unroll.disable"}
